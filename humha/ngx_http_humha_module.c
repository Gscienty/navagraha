#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include "humha_process.h"

#define NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT 16

typedef struct {
    ngx_http_upstream_conf_t upstream;
    ngx_str_t call_namespace;
    ngx_str_t executor;
    ngx_str_t args[NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT];
} ngx_http_humha_loc_conf_t;

static char * ngx_http_humha(ngx_conf_t * cf, ngx_command_t * cmd, void * conf);
static char * ngx_http_humha_recv(ngx_conf_t * cf, ngx_command_t * cmd, void * conf);
static char * ngx_http_humha_call(ngx_conf_t * cf, ngx_command_t * cmd, void * conf);

static void * ngx_http_humha_create_loc_conf(ngx_conf_t * cf);

static ngx_int_t ngx_http_humha_handler(ngx_http_request_t * r);
static void ngx_http_humha_readed_body_handler(ngx_http_request_t * r);
static ngx_int_t ngx_http_humha_process_input(ngx_http_request_t * r, humha_process_t * p);
static ngx_int_t ngx_http_humha_process_output(ngx_http_request_t * r, humha_process_t * p);

static ngx_int_t ngx_http_humha_call_create_request(ngx_http_request_t * r);
static ngx_int_t ngx_http_humha_call_process_status_line(ngx_http_request_t * r);
static void ngx_http_humha_call_abort_request(ngx_http_request_t * r);
static void ngx_http_humha_call_finalize_request(ngx_http_request_t * r, ngx_int_t rc);
static ngx_int_t ngx_http_humha_call_process_header(ngx_http_request_t * r);
static ngx_int_t ngx_http_humha_call_copy_filter(ngx_event_pipe_t * p, ngx_buf_t *buf);
static ngx_int_t ngx_http_humha_call_input_filter_init(void * data);
static ngx_int_t ngx_http_humha_call_chunked_filter(ngx_event_pipe_t * p, ngx_buf_t * buf);
static ngx_int_t ngx_http_humha_call_non_buffered_chunked_filter(void * data, ssize_t bytes);

static ngx_int_t ngx_http_humha_request_is_async(ngx_list_t * headers, ngx_str_t * async_cb);

static ngx_command_t ngx_http_humha_module_commands[] = {
    {
        ngx_string("humha_recv"),
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE3,
        ngx_http_humha,
        NGX_HTTP_LOC_CONF_OFFSET,
        0,
        NULL
    },

    {
        ngx_string("humha_call"),
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
        ngx_http_humha,
        NGX_HTTP_LOC_CONF_OFFSET,
        0,
        NULL
    },

    ngx_null_command
};

static ngx_http_module_t ngx_http_humha_module_ctx = {
    NULL, // preconfiguration
    NULL, // postconfiguration
    NULL, // create main configuration
    NULL, // init main configuration
    NULL, // create server configuration
    NULL, // init server configuration
    ngx_http_humha_create_loc_conf, // create location configuration
    NULL  // merge location configuration
};

ngx_module_t ngx_http_humha_module = {
    NGX_MODULE_V1,
    &ngx_http_humha_module_ctx,
    ngx_http_humha_module_commands,
    NGX_HTTP_MODULE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NGX_MODULE_V1_PADDING
};

static void * ngx_http_humha_create_loc_conf(ngx_conf_t * cf)
{
    ngx_http_humha_loc_conf_t * conf;
    ngx_uint_t args_idx;

    conf = ngx_palloc(cf->pool, sizeof(ngx_http_humha_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }
    conf->call_namespace.data = NULL;
    conf->call_namespace.len = 0;
    conf->executor.data = NULL;
    conf->executor.len = 0;
    for (args_idx = 0; args_idx < NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT; args_idx++) {
        conf->args->data = NULL;
        conf->args->len = 0;
    }
    conf->upstream.connect_timeout = 60000;
    conf->upstream.send_timeout = 60000;
    conf->upstream.read_timeout = 60000;
    conf->upstream.store_access = 0600;

    conf->upstream.buffering = 0;
    conf->upstream.bufs.num = 8;
    conf->upstream.bufs.size = ngx_pagesize;
    conf->upstream.buffer_size = ngx_pagesize;
    conf->upstream.busy_buffers_size = ngx_pagesize << 1;

    conf->upstream.max_temp_file_size = 1024 * 1024 * 1024;
    conf->upstream.temp_file_write_size = ngx_pagesize << 1;

    conf->upstream.hide_headers = NGX_CONF_UNSET_PTR;
    conf->upstream.pass_headers = NGX_CONF_UNSET_PTR;

    return conf;
}

static char * ngx_http_humha(ngx_conf_t * cf, ngx_command_t * cmd, void * conf)
{
    ngx_str_t * value = cf->args->elts;
    if (ngx_strcmp("humha_recv", value[0].data) == 0) {
        return ngx_http_humha_recv(cf, cmd, conf);
    }
    else if (ngx_strcmp("humha_call", value[0].data) == 0) {
        return ngx_http_humha_call(cf, cmd, conf);
    }
    else {
        return NGX_CONF_ERROR;
    }
}

static char * ngx_http_humha_call(ngx_conf_t * cf, ngx_command_t * cmd, void * conf)
{
    (void) cmd;
    ngx_http_core_loc_conf_t * ccf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    ngx_http_humha_loc_conf_t * humha_conf = conf;
    ngx_str_t * value = cf->args->elts;
    const char * call_namespace_base = getenv((char *) value[1].data);

    humha_conf->call_namespace.data = (u_char *) call_namespace_base;
    humha_conf->call_namespace.len = 0;
    if (call_namespace_base != NULL) {
        humha_conf->call_namespace.len = ngx_strlen(call_namespace_base);
    }

    ccf->handler = ngx_http_humha_handler;

    return NGX_CONF_OK;
}

static char * ngx_http_humha_recv(ngx_conf_t * cf, ngx_command_t * cmd, void * conf)
{
    (void) cmd;
    ngx_http_core_loc_conf_t * ccf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    ngx_http_humha_loc_conf_t * humha_conf = conf;
    ngx_str_t * value = cf->args->elts;
    const char * executor_executor_base  = getenv((char *) value[1].data);
    const char * executor_name_base = getenv((char *) value[2].data);
    const char * executor_args_base = getenv((char *) value[3].data);
    const char * args_delimiter = NULL;
    ngx_uint_t args_idx;

    if (executor_executor_base == NULL) {
        return NGX_CONF_ERROR;
    }
    humha_conf->executor.data = (u_char *) executor_executor_base;
    humha_conf->executor.len = ngx_strlen(executor_executor_base);
    if (executor_name_base == NULL) {
        return NGX_CONF_ERROR;
    }
    humha_conf->args[0].data = (u_char *) executor_name_base;
    humha_conf->args[0].len = ngx_strlen(executor_name_base);

    if (executor_args_base != NULL) {
        for (args_idx = 1; args_idx < NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT - 1 && *executor_args_base; args_idx++) {
            if (*executor_args_base == ' ') {
                args_idx--;
                executor_args_base++;
                continue;
            }

            args_delimiter = ngx_strchr(executor_args_base, ' ');
            if (args_delimiter == NULL) {
                args_delimiter = executor_args_base + ngx_strlen(executor_args_base);
            }
            humha_conf->args[args_idx].len = (size_t) (args_delimiter - executor_args_base);
            humha_conf->args[args_idx].data = ngx_palloc(cf->pool, humha_conf->args[args_idx].len + 1);
            ngx_memzero(humha_conf->args[args_idx].data, humha_conf->args[args_idx].len + 1);
            ngx_memcpy(humha_conf->args[args_idx].data, executor_args_base, humha_conf->args[args_idx].len);
            executor_args_base = args_delimiter;
        }

        if (*executor_args_base != 0) {
            return NGX_CONF_ERROR;
        }
    }

    ccf->handler = ngx_http_humha_handler;

    return NGX_CONF_OK;
}

#define ngx_chain_free_link(p, x) ({\
                                   ngx_chain_t * __tmp = (x)->next;\
                                   ngx_pfree((p), (x));\
                                   __tmp; \
                                   })

#define NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE 1024

static ngx_int_t ngx_http_humha_handler(ngx_http_request_t * r)
{
    size_t uri_len;
    ngx_http_humha_loc_conf_t * lcf;
    ngx_http_upstream_t * u;
    ngx_str_t * url;
    struct sockaddr_in * peer_sock = NULL;
    struct hostent * host = NULL;
    char * peer_ip_str = NULL;
    ngx_int_t ret = 0;

    if (r->uri.len == 1) {
        ret = ngx_http_read_client_request_body(r, ngx_http_humha_readed_body_handler);
    }
    else {
        if (ngx_http_upstream_create(r) != NGX_OK) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }
        lcf = ngx_http_get_module_loc_conf(r, ngx_http_humha_module);

        u = r->upstream;
        u->conf = &lcf->upstream;
        u->output.tag = (ngx_buf_tag_t) &ngx_http_humha_module;

        url = ngx_palloc(r->pool, sizeof(ngx_url_t));
        if (url == NULL) {
            return NGX_ERROR;
        }
        ngx_http_set_ctx(r, url, ngx_http_humha_module);

        uri_len = r->uri_end - r->uri_start;
        url->len = lcf->call_namespace.len + uri_len;
        url->data = ngx_palloc(r->pool, url->len + 1);
        ngx_memzero(url->data, url->len + 1);
        ngx_memcpy(url->data, r->uri_start + 1, uri_len - 1);
        url->data[uri_len - 1] = '.';
        ngx_memcpy(url->data + uri_len, lcf->call_namespace.data, lcf->call_namespace.len);

        u->create_request = ngx_http_humha_call_create_request;
        u->abort_request = ngx_http_humha_call_abort_request;
        u->process_header = ngx_http_humha_call_process_status_line;
        u->finalize_request = ngx_http_humha_call_finalize_request;

        u->resolved = ngx_palloc(r->pool, sizeof(ngx_http_upstream_resolved_t));
        if (u->resolved == NULL) {
            return NGX_ERROR;
        }
        peer_sock = ngx_palloc(r->pool, sizeof(struct sockaddr_in));
        if (peer_sock == NULL) {
            return NGX_ERROR;
        }
        u->resolved->sockaddr = (struct sockaddr *) peer_sock;
        u->resolved->socklen = sizeof(struct sockaddr_in);
        u->resolved->naddrs = 1;
        u->resolved->port = 80;
        host = gethostbyname((char *) url->data);
        if (host == NULL) {
            return NGX_ERROR;
        }
        peer_sock->sin_family = AF_INET;
        peer_sock->sin_port = htons((in_port_t) 80);
        peer_ip_str = inet_ntoa(*(struct in_addr *) (host->h_addr_list[0]));
        peer_sock->sin_addr.s_addr = inet_addr(peer_ip_str);

        u->buffering = 0;

        u->pipe = ngx_palloc(r->pool, sizeof(ngx_event_pipe_t));
        if (u->pipe == NULL) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }
        u->pipe->input_filter = ngx_http_humha_call_copy_filter;
        u->pipe->input_ctx = r;

        u->input_filter_init = ngx_http_humha_call_input_filter_init;
        u->input_filter = ngx_http_humha_call_non_buffered_chunked_filter;
        u->input_filter_ctx = r;

        r->main->count++;

        ret = ngx_http_read_client_request_body(r, ngx_http_upstream_init);
    }

    if (ret >= NGX_HTTP_SPECIAL_RESPONSE) {
        return ret;
    }

    ngx_http_finalize_request(r, NGX_DONE);
    return NGX_DONE;
}

static ngx_int_t ngx_http_humha_request_is_async(ngx_list_t * headers, ngx_str_t * async_cb)
{
    ngx_list_part_t * part = &headers->part;
    ngx_table_elt_t * header = NULL;
    ngx_uint_t idx;

    for (idx = 0; ; idx++) {
        if (idx >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            header = part->elts;
            idx = 0;
        }
        if (ngx_strcmp(header[idx].lowcase_key, "async-callback") == 0) {
            async_cb->data = header[idx].value.data;
            async_cb->len = header[idx].value.len;

            return 1;
        }
    }

    return 0;
}

static void ngx_http_humha_readed_body_handler(ngx_http_request_t * r)
{
    ngx_http_humha_loc_conf_t * lcf;
    humha_process_t p;
    ngx_int_t retcode;
    u_char * args[NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT] = { NULL }; 
    ngx_uint_t args_idx;
    ngx_str_t async_cb = { 0, NULL };
    ngx_chain_t async_out = { NULL, NULL };

    lcf = ngx_http_get_module_loc_conf(r, ngx_http_humha_module);
    if (lcf == NULL || lcf->executor.data == NULL) {
        return;
    }
    for (args_idx = 0; args_idx < NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT && lcf->args[args_idx].data != NULL; args_idx++) {
        args[args_idx] = lcf->args[args_idx].data;
    }
    p.is_async = ngx_http_humha_request_is_async(&r->headers_in.headers, &async_cb);

    if (humha_process(lcf->executor.data, (const u_char **) args, &p, &async_cb) < 0) {
        goto output;
    }

    retcode = ngx_http_humha_process_input(r, &p);
    if (retcode != NGX_OK) {
        r->headers_out.status = NGX_HTTP_INTERNAL_SERVER_ERROR;
        humha_process_kill(&p);
        humha_process_close(&p);
        goto output;
    }

    if (p.is_async == 1) {

        r->headers_out.status = NGX_HTTP_ACCEPTED;
        r->headers_out.content_length_n = strlen("Accepted");

        async_out.buf = ngx_create_temp_buf(r->pool, strlen("Accepted"));
        async_out.buf->last_buf = 1;
        ngx_memcpy(async_out.buf->pos, "Accepted", strlen("Accepted"));
        async_out.buf->last = async_out.buf->pos + strlen("Accepted");

        ngx_http_send_header(r);
        retcode = ngx_http_output_filter(r, &async_out);
        return;
    }

    retcode = humha_process_wait(&p);
    if (retcode != 0) {
        r->headers_out.status = NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    else {
        r->headers_out.status = NGX_HTTP_OK;
    }

output:
    retcode = ngx_http_humha_process_output(r, &p);
    humha_process_close(&p);
}

static ngx_int_t ngx_http_humha_process_input(ngx_http_request_t * r, humha_process_t * p)
{
    ngx_chain_t * cur_chain;
    if (r->request_body == NULL || r->request_body->bufs == NULL) {
        write(p->in, NULL, 0);
        humha_process_in_close(p);
        return NGX_OK;
    }

    for (cur_chain = r->request_body->bufs; cur_chain != NULL; cur_chain = cur_chain->next) {
        write(p->in, cur_chain->buf->pos, ngx_buf_size(cur_chain->buf));
    }
    humha_process_in_close(p);

    return NGX_OK;
}

static ngx_int_t ngx_http_humha_process_output(ngx_http_request_t * r, humha_process_t * p)
{
    ngx_int_t retcode;
    ngx_int_t yield_size = 0;
    ngx_int_t remain_size = NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE;
    ngx_chain_t * out = ngx_alloc_chain_link(r->pool);
    ngx_chain_t * cur_chain = out;
    out->next = NULL;
    out->buf = ngx_create_temp_buf(r->pool, NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE);
    out->buf->last = out->buf->pos;
    out->buf->last_buf = 0;

    r->headers_out.content_length_n = 0;
    ngx_str_set(&r->headers_out.content_type, "application/octet-stream");
    if (ngx_http_set_content_type(r) != NGX_OK) {
        return NGX_ERROR;
    }

    while ((yield_size = read(p->out, cur_chain->buf->pos + (NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE - remain_size), remain_size)) > 0) {
        r->headers_out.content_length_n += yield_size;
        remain_size += yield_size;
        cur_chain->buf->last += yield_size;

        if (remain_size == NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE) {
            cur_chain->next = ngx_alloc_chain_link(r->pool);
            cur_chain = cur_chain->next;
            cur_chain->buf = ngx_create_temp_buf(r->pool, NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE);
            cur_chain->buf->last = cur_chain->buf->pos;
            cur_chain->buf->last_buf = 0;
            remain_size = NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE;
        }
    }
    cur_chain->buf->last_buf = 1;

    retcode = ngx_http_send_header(r);

    if (retcode == NGX_ERROR || retcode > NGX_OK || r->header_only) {
        return NGX_ERROR;
    }

    retcode = ngx_http_output_filter(r, out);

    cur_chain = out;
    while ((cur_chain = ngx_chain_free_link(r->pool, cur_chain)) != NULL);

    return NGX_OK;
}

static char ngx_http_humha_call_http_version[] = "HTTP/1.0" CRLF;

static ngx_int_t ngx_http_humha_call_create_request(ngx_http_request_t * r)
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

    url = ngx_http_get_module_ctx(r, ngx_http_humha_module);

    if (u->method.len) {
        method = u->method;
    }
    else {
        method = r->method_name;
    }

    len += method.len + 1
        + 1 + 1
        + sizeof(ngx_http_humha_call_http_version) - 1
        + sizeof(CRLF) - 1;

    part = &r->headers_in.headers.part;
    header = part->elts;
    for (idx = 0; ; idx++) {
        if (idx >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            header = part->elts;
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
    b->last = ngx_copy(b->last, ngx_http_humha_call_http_version, sizeof(ngx_http_humha_call_http_version) - 1);

    part = &r->headers_in.headers.part;
    header = part->elts;
    for (idx = 0; ; idx++) {
        if (idx >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            header = part->elts;
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
            b = ngx_alloc_buf(r->pool);
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

static ngx_int_t ngx_http_humha_call_process_status_line(ngx_http_request_t * r)
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
    u->headers_in.status_line.data = ngx_palloc(r->pool, len);
    if (u->headers_in.status_line.data == NULL) {
        return NGX_ERROR;
    }
    ngx_memcpy(u->headers_in.status_line.data, status.start, len);

    // because use HTTP/1.0
    u->headers_in.connection_close = 1;

    u->process_header = ngx_http_humha_call_process_header;

    return ngx_http_humha_call_process_header(r);
}

static ngx_int_t ngx_http_humha_call_process_header(ngx_http_request_t * r)
{
    ngx_int_t ret;
    ngx_table_elt_t * h;

    for ( ;; ) {
        ret = ngx_http_parse_header_line(r, &r->upstream->buffer, 1);

        switch (ret) {
        case NGX_OK:
            h = ngx_list_push(&r->upstream->headers_in.headers);
            if (h == NULL) {
                return NGX_ERROR;
            }

            h->hash = r->header_hash;

            h->key.len = r->header_name_end - r->header_name_start;
            h->value.len = r->header_end - r->header_start;

            h->key.data = ngx_palloc(r->pool,
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

static void ngx_http_humha_call_abort_request(ngx_http_request_t * r)
{
    (void) r;

    return;
}

static void ngx_http_humha_call_finalize_request(ngx_http_request_t * r, ngx_int_t ret)
{
    (void) r;
    (void) ret;

    return;
}

static ngx_int_t ngx_http_humha_call_copy_filter(ngx_event_pipe_t * p, ngx_buf_t *buf)
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
        r = p->input_ctx;
        p->upstream_done = 1;
        r->upstream->keepalive = !r->upstream->headers_in.connection_close;
    }
    else if (p->length < 0) {
        r = p->input_ctx;
        p->upstream_done = 1;
    }

    return NGX_OK;
}

static ngx_int_t ngx_http_humha_call_input_filter_init(void * data)
{
    ngx_http_request_t * r = data;
    ngx_http_upstream_t * u;

    u = r->upstream;
    
    if (u->headers_in.status_n == NGX_HTTP_NO_CONTENT
        || u->headers_in.status_n == NGX_HTTP_NOT_MODIFIED) {
        u->pipe->length = 0;
        u->length = 0;
        u->keepalive = !u->headers_in.connection_close;
    }
    else if (u->headers_in.chunked) {
        u->pipe->input_filter = ngx_http_humha_call_chunked_filter;
        u->pipe->length = 3;
        u->input_filter = ngx_http_humha_call_non_buffered_chunked_filter;
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

static ngx_int_t ngx_http_humha_call_chunked_filter(ngx_event_pipe_t * p, ngx_buf_t * buf)
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

    r = p->input_ctx;

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

static ngx_int_t ngx_http_humha_call_non_buffered_chunked_filter(void * data, ssize_t bytes)
{
    ngx_http_request_t * r = data;
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
