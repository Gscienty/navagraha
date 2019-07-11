#include "ngx_http_humha_upstream.h"

extern ngx_module_t ngx_http_humha_module;

static char ngx_http_humha_upstream_http_version[] = "HTTP/1.0" CRLF;

static ngx_int_t ngx_http_humha_upstream_create_request(ngx_http_request_t * r);
static void ngx_http_humha_upstream_abort_request(ngx_http_request_t * r);
static void ngx_http_humha_upstream_finalize_request(ngx_http_request_t * r, ngx_int_t ret);
static ngx_int_t ngx_http_humha_upstream_process_status_line(ngx_http_request_t * r);
static ngx_int_t ngx_http_humha_upstream_process_header(ngx_http_request_t * r);
static ngx_int_t ngx_http_humha_upstream_copy_filter(ngx_event_pipe_t * p, ngx_buf_t *buf);
static ngx_int_t ngx_http_humha_upstream_input_filter_init(void * data);
static ngx_int_t ngx_http_humha_upstream_chunked_filter(ngx_event_pipe_t * p, ngx_buf_t * buf);
static ngx_int_t ngx_http_humha_upstream_non_buffered_chunked_filter(void * data, ssize_t bytes);

ngx_int_t ngx_http_humha_upstream(ngx_http_request_t * r, ngx_http_humha_loc_conf_t * lcf, ngx_http_humha_upstream_resolve_fptr_t resolve_fptr, ngx_int_t is_unixsock)
{
    ngx_int_t ret = 0;
    ngx_http_upstream_t * u;
    ngx_str_t * url;
    size_t uri_len;

    if (resolve_fptr == NULL) {
        return NGX_ERROR;
    }

    if (ngx_http_upstream_create(r) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    u = r->upstream;
    u->conf = &lcf->upstream;
    u->output.tag = (ngx_buf_tag_t) &ngx_http_humha_module;

    url = (ngx_str_t *) ngx_palloc(r->pool, sizeof(ngx_str_t));
    if (url == NULL) {
        return NGX_ERROR;
    }
    ngx_http_set_ctx(r, url, ngx_http_humha_module);

    u->create_request = ngx_http_humha_upstream_create_request;
    u->abort_request = ngx_http_humha_upstream_abort_request;
    u->process_header = ngx_http_humha_upstream_process_status_line;
    u->finalize_request = ngx_http_humha_upstream_finalize_request;

    u->resolved = (ngx_http_upstream_resolved_t *) ngx_palloc(r->pool, sizeof(ngx_http_upstream_resolved_t));
    if (u->resolved == NULL) {
        return NGX_ERROR;
    }

    if (is_unixsock != 0) {
        url->data = lcf->executor.data;
        url->len = lcf->executor.len;
    }
    else {
        uri_len = r->uri_end - r->uri_start;
        url->len = lcf->call_namespace.len + uri_len;
        url->data = (u_char *) ngx_palloc(r->pool, url->len + 1);
        ngx_memzero(url->data, url->len + 1);
        ngx_memcpy(url->data, r->uri_start + 1, uri_len - 1);
        url->data[uri_len - 1] = '.';
        ngx_memcpy(url->data + uri_len, lcf->call_namespace.data, lcf->call_namespace.len);
    }
    if (resolve_fptr(r->pool, u->resolved, url) != NGX_OK) {
        return NGX_ERROR;
    }

    u->buffering = 0;

    u->pipe = (ngx_event_pipe_t *) ngx_palloc(r->pool, sizeof(ngx_event_pipe_t));
    if (u->pipe == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    u->pipe->input_filter = ngx_http_humha_upstream_copy_filter;
    u->pipe->input_ctx = r;

    u->input_filter_init = ngx_http_humha_upstream_input_filter_init;
    u->input_filter = ngx_http_humha_upstream_non_buffered_chunked_filter;
    u->input_filter_ctx = r;

    r->main->count++;

    ret = ngx_http_read_client_request_body(r, ngx_http_upstream_init);

    return ret;
}

static ngx_int_t ngx_http_humha_upstream_create_request(ngx_http_request_t * r)
{
    ngx_http_upstream_t * u = r->upstream;
    ngx_list_part_t * part;
    ngx_table_elt_t * header = NULL;
    ngx_chain_t * cl;
    ngx_chain_t * body;
    ngx_buf_t * b;
    ngx_str_t method;
    ngx_str_t * url;
    size_t len = 0;
    ngx_uint_t idx;

    url = (ngx_str_t *) ngx_http_get_module_ctx(r, ngx_http_humha_module);

    if (u->method.len) {
        method = u->method;
    }
    else {
        method = r->method_name;
    }

    len += method.len + 1
        + 1 + 1
        + sizeof(ngx_http_humha_upstream_http_version) - 1
        + sizeof(CRLF) - 1;

    part = &r->headers_in.headers.part;
    header = (ngx_table_elt_t *) part->elts;
    for (idx = 0; ; idx++) {
        if (idx >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            header = (ngx_table_elt_t *) part->elts;
            idx = 0;
        }
        len += header[idx].key.len + sizeof(": ") - 1
            + header[idx].value.len + sizeof(CRLF) - 1;

    }

    b = ngx_create_temp_buf(r->pool, len);
    if (b == NULL) {
        return NGX_ERROR;
    }

    cl = ngx_alloc_chain_link(r->pool);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    cl->buf = b;

    b->last = ngx_copy(b->last, method.data, method.len);
    *b->last++ = ' ';
    *b->last++ = '/';
    *b->last++ = ' ';
    b->last = ngx_copy(b->last, ngx_http_humha_upstream_http_version, sizeof(ngx_http_humha_upstream_http_version) - 1);

    part = &r->headers_in.headers.part;
    header = (ngx_table_elt_t *) part->elts;
    for (idx = 0; ; idx++) {
        if (idx >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            header = (ngx_table_elt_t *) part->elts;
            idx = 0;
        }
        
        if (ngx_strncasecmp(header[idx].key.data, (u_char *) "host", header[idx].key.len) == 0) {
            continue;
        }

        b->last = ngx_copy(b->last, header[idx].key.data, header[idx].key.len);
        *b->last++ = ':';
        *b->last++ = ' ';
        b->last = ngx_copy(b->last, header[idx].value.data, header[idx].value.len);
        *b->last++ = CR;
        *b->last++ = LF;
    }

    b->last = ngx_copy(b->last, "Host", 4);
    *b->last++ = ':';
    *b->last++ = ' ';
    b->last = ngx_copy(b->last, url->data, url->len);
    *b->last++ = CR;
    *b->last++ = LF;

    *b->last++ = CR;
    *b->last++ = LF;

    if (r->request_body_no_buffering) {
        u->request_bufs = cl;
    }
    else {
        body = u->request_bufs;
        u->request_bufs = cl;

        while (body) {
            b = (ngx_buf_t *) ngx_alloc_buf(r->pool);
            if (b == NULL) {
                return NGX_ERROR;
            }

            ngx_memcpy(b, body->buf, sizeof(ngx_buf_t));
            
            cl->next = ngx_alloc_chain_link(r->pool);
            if (cl->next == NULL) {
                return NGX_ERROR;
            }

            cl = cl->next;
            cl->buf = b;

            body = body->next;
        }
    }

    b->flush = 1;
    cl->next = NULL;

    return NGX_OK;
}

static void ngx_http_humha_upstream_abort_request(ngx_http_request_t * r)
{
    (void) r;

    return;
}

static void ngx_http_humha_upstream_finalize_request(ngx_http_request_t * r, ngx_int_t ret)
{
    (void) r;
    (void) ret;

    return;
}

static ngx_int_t ngx_http_humha_upstream_process_status_line(ngx_http_request_t * r)
{
    size_t len;
    ngx_http_status_t status;
    ngx_http_upstream_t * u = r->upstream;
    ngx_int_t ret;

    ret = ngx_http_parse_status_line(r, &u->buffer, &status);
    if (ret == NGX_AGAIN) {
        return ret;
    }

    if (ret == NGX_ERROR) {
        r->http_version = NGX_HTTP_VERSION_9;
        u->state->status = NGX_HTTP_OK;
        u->headers_in.connection_close = 1;

        return NGX_OK;
    }

    if (u->state && u->state->status == 0) {
        u->state->status = status.code;
    }

    u->headers_in.status_n = status.code;
    len = status.end - status.start;
    u->headers_in.status_line.len = len;
    u->headers_in.status_line.data = (u_char *) ngx_palloc(r->pool, len);
    if (u->headers_in.status_line.data == NULL) {
        return NGX_ERROR;
    }
    ngx_memcpy(u->headers_in.status_line.data, status.start, len);

    // because use HTTP/1.0
    u->headers_in.connection_close = 1;

    u->process_header = ngx_http_humha_upstream_process_header;

    return ngx_http_humha_upstream_process_header(r);
}

static ngx_int_t ngx_http_humha_upstream_process_header(ngx_http_request_t * r)
{
    ngx_int_t ret;
    ngx_table_elt_t * h;

    for ( ;; ) {
        ret = ngx_http_parse_header_line(r, &r->upstream->buffer, 1);

        switch (ret) {
        case NGX_OK:
            h = (ngx_table_elt_t *) ngx_list_push(&r->upstream->headers_in.headers);
            if (h == NULL) {
                return NGX_ERROR;
            }

            h->hash = r->header_hash;

            h->key.len = r->header_name_end - r->header_name_start;
            h->value.len = r->header_end - r->header_start;

            h->key.data = (u_char *) ngx_palloc(r->pool,
                                                h->key.len + 1 + h->value.len + 1 + h->key.len);
            if (h->key.data == NULL) {
                h->hash = 0;
                return NGX_ERROR;
            }
            h->value.data = h->key.data + h->key.len + 1;
            h->lowcase_key = h->key.data + h->key.len + 1 + h->value.len + 1;

            ngx_memcpy(h->key.data, r->header_name_start, h->key.len);
            h->key.data[h->key.len] = 0;
            ngx_memcpy(h->value.data, r->header_start, h->value.len);
            h->value.data[h->value.len] = 0;
            if (h->key.len == r->lowcase_index) {
                ngx_memcpy(h->lowcase_key, r->lowcase_header, h->key.len);
            }
            else {
                ngx_strlow(h->lowcase_key, h->key.data, h->key.len);
            }
            break;
        case NGX_HTTP_PARSE_HEADER_DONE:
            return NGX_OK;
        case NGX_AGAIN:
            return NGX_AGAIN;
        default:
            return NGX_HTTP_UPSTREAM_INVALID_HEADER;
        }
    }
}

static ngx_int_t ngx_http_humha_upstream_copy_filter(ngx_event_pipe_t * p, ngx_buf_t *buf)
{
    ngx_buf_t * b;
    ngx_chain_t * cl;
    ngx_http_request_t * r;

    if (buf->pos == buf->last) {
        return NGX_OK;
    }

    cl = ngx_chain_get_free_buf(p->pool, &p->free);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    b = cl->buf;
    
    ngx_memcpy(b, buf, sizeof(ngx_buf_t));
    b->shadow = buf;
    b->tag = p->tag;
    b->last_shadow = 1;
    b->recycled = 1;
    buf->shadow = b;

    if (p->in) {
        *p->last_in = cl;
    }
    else {
        p->in = cl;
    }
    p->last_in = &cl->next;

    if (p->length == -1) {
        return NGX_OK;
    }

    p->length -= b->last - b->pos;

    if (p->length == 0) {
        r = (ngx_http_request_t *) p->input_ctx;
        p->upstream_done = 1;
        r->upstream->keepalive = !r->upstream->headers_in.connection_close;
    }
    else if (p->length < 0) {
        r = (ngx_http_request_t *) p->input_ctx;
        p->upstream_done = 1;
    }

    return NGX_OK;
}

static ngx_int_t ngx_http_humha_upstream_input_filter_init(void * data)
{
    ngx_http_request_t * r = (ngx_http_request_t *) data;
    ngx_http_upstream_t * u;

    u = r->upstream;
    
    if (u->headers_in.status_n == NGX_HTTP_NO_CONTENT
        || u->headers_in.status_n == NGX_HTTP_NOT_MODIFIED) {
        u->pipe->length = 0;
        u->length = 0;
        u->keepalive = !u->headers_in.connection_close;
    }
    else if (u->headers_in.chunked) {
        u->pipe->input_filter = ngx_http_humha_upstream_chunked_filter;
        u->pipe->length = 3;
        u->input_filter = ngx_http_humha_upstream_non_buffered_chunked_filter;
        u->length = 1;
    }
    else if (u->headers_in.content_length_n == 0) {
        u->pipe->length = 0;
        u->length = 0;
        u->keepalive = !u->headers_in.connection_close;
    }
    else {
        u->pipe->length = u->headers_in.content_length_n;
        u->length = u->headers_in.content_length_n;
    }

    return NGX_OK;
}

static ngx_int_t ngx_http_humha_upstream_chunked_filter(ngx_event_pipe_t * p, ngx_buf_t * buf)
{
    ngx_int_t ret;
    ngx_buf_t * b;
    ngx_buf_t ** prev;
    ngx_chain_t * cl;
    ngx_http_request_t * r;
    ngx_http_chunked_t chunked;

    if (buf->last == buf->pos) {
        return NGX_OK;
    }

    r = (ngx_http_request_t *) p->input_ctx;

    b = NULL;
    prev = &b->shadow;

    for ( ;; ) {
        ret = ngx_http_parse_chunked(r, buf, &chunked);
        switch (ret) {
        case NGX_OK:
            cl = ngx_chain_get_free_buf(p->pool, &p->free);
            if (cl == NULL) {
                return NGX_ERROR;
            }
            b = cl->buf;
            ngx_memzero(b, sizeof(ngx_buf_t));
            b->pos = buf->pos;
            b->start = buf->start;
            b->end = buf->end;
            b->tag = buf->tag;
            b->temporary = 1;
            b->recycled = 1;

            *prev = b;
            prev = &b->shadow;

            if (p->in) {
                *p->last_in = cl;
            }
            else {
                p->in = cl;
            }
            p->last_in = &cl->next;

            b->num = buf->num;

            if (buf->last - buf->pos >= chunked.size) {
                buf->pos += (size_t) chunked.size;
                b->last = buf->pos;
                chunked.size = 0;
            }
            else {
                chunked.size -= buf->last - buf->pos;
                buf->pos = buf->last;
                b->last = buf->last;
            }

            break;

        case NGX_DONE:
            p->upstream_done = 1;
            r->upstream->keepalive = !r->upstream->headers_in.connection_close;

            goto out_loop;

        case NGX_AGAIN:
            p->length = chunked.length;

            goto out_loop;

        default:
            return NGX_ERROR;
        }
    }

out_loop:
    if (b) {
        b->shadow = buf;
        b->last_shadow = 1;

        return NGX_OK;
    }

    if (ngx_event_pipe_add_free_buf(p, buf) != NGX_OK) {
        return NGX_ERROR;
    }

    return NGX_OK;
}

static ngx_int_t ngx_http_humha_upstream_non_buffered_chunked_filter(void * data, ssize_t bytes)
{
    ngx_http_request_t * r = (ngx_http_request_t *) data;
    ngx_buf_t * b;
    ngx_chain_t * cl;
    ngx_chain_t ** ll;
    ngx_http_upstream_t * u;

    u = r->upstream;

    for (cl = u->out_bufs, ll = &u->out_bufs; cl; cl = cl->next) {
        ll = &cl->next;
    }

    cl = ngx_chain_get_free_buf(r->pool, &u->free_bufs);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    *ll = cl;

    cl->buf->flush = 1;
    cl->buf->memory = 1;

    b = &u->buffer;

    cl->buf->pos = b->last;
    b->last += bytes;
    cl->buf->last = b->last;
    cl->buf->tag = u->output.tag;

    if (u->length == -1) {
        return NGX_OK;
    }

    u->length -= bytes;

    if (u->length == 0) {
        u->keepalive = !u->headers_in.connection_close;
    }

    return NGX_OK;
}
