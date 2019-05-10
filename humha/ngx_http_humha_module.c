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
static ngx_int_t ngx_http_humha_call_process_header(ngx_http_request_t * r);

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
    conf->upstream.local = NGX_CONF_UNSET_PTR;
    conf->upstream.socket_keepalive = NGX_CONF_UNSET;
    conf->upstream.next_upstream_tries = NGX_CONF_UNSET_UINT;
    conf->upstream.connect_timeout = NGX_CONF_UNSET_MSEC;
    conf->upstream.send_timeout = NGX_CONF_UNSET_MSEC;
    conf->upstream.read_timeout = NGX_CONF_UNSET_MSEC;
    conf->upstream.next_upstream_timeout = NGX_CONF_UNSET_MSEC;

    conf->upstream.buffer_size = NGX_CONF_UNSET_SIZE;

    conf->upstream.cyclic_temp_file = 0;
    conf->upstream.buffering = 0;
    conf->upstream.ignore_client_abort = 0;
    conf->upstream.send_lowat = 0;
    conf->upstream.bufs.num = 0;
    conf->upstream.busy_buffers_size = 0;
    conf->upstream.max_temp_file_size = 0;
    conf->upstream.temp_file_write_size = 0;
    conf->upstream.intercept_errors = 1;
    conf->upstream.intercept_404 = 1;
    conf->upstream.pass_request_body = 0;
    conf->upstream.force_ranges = 1;

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
    char * chr;
    ngx_http_humha_loc_conf_t * lcf;
    ngx_http_upstream_t * u;
    ngx_int_t ret = 0;

    if (r->uri.len == 1) {
        ret = ngx_http_read_client_request_body(r, ngx_http_humha_readed_body_handler);
    }
    else {
        if (ngx_http_upstream_create(r) != NGX_OK) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }
        u = r->upstream;
        u->output.tag = (ngx_buf_tag_t) &ngx_http_humha_module;

        lcf = ngx_http_get_module_loc_conf(r, ngx_http_humha_module);

        u->uri.len = 7 + lcf->call_namespace.len + r->uri.len;
        u->uri.data = ngx_palloc(r->pool, u->uri.len + 1);
        ngx_memzero(u->uri.data, u->uri.len + 1);
        ngx_memcpy(u->uri.data, "http://", 7);
        ngx_memcpy(u->uri.data + 7, r->uri.data + 1, r->uri.len - 1);
        u->uri.data[r->uri.len - 1] = '.';
        ngx_memcpy(u->uri.data + 7 + r->uri.len, lcf->call_namespace.data, lcf->call_namespace.len);
        while ((chr = ngx_strchr(u->uri.data + 7, '/')) != NULL) {
            *chr = '-';
        }

        u->conf = &lcf->upstream;

        u->schema.data = u->uri.data;
        u->schema.len = 7;

        // TODO register 
        u->create_request = ngx_http_humha_call_create_request;

        ngx_pfree(r->pool, u->uri.data);
        u->uri.data = NULL;
        u->uri.len = 0;

    }

    if (ret >= NGX_HTTP_SPECIAL_RESPONSE) {
        return ret;
    }

    ngx_http_finalize_request(r, NGX_DONE);
    return ret;
}

static void ngx_http_humha_readed_body_handler(ngx_http_request_t * r)
{
    ngx_http_humha_loc_conf_t * lcf;
    humha_process_t p;
    ngx_int_t retcode;
    u_char * args[NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT] = { NULL }; 
    ngx_uint_t args_idx;

    lcf = ngx_http_get_module_loc_conf(r, ngx_http_humha_module);
    if (lcf == NULL || lcf->executor.data == NULL) {
        return;
    }
    for (args_idx = 0; args_idx < NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT && lcf->args[args_idx].data != NULL; args_idx++) {
        args[args_idx] = lcf->args[args_idx].data;
    }

    if (humha_process(lcf->executor.data, (const u_char **) args, &p) < 0) {
        goto output;
    }

    retcode = ngx_http_humha_process_input(r, &p);
    if (retcode != NGX_OK) {
        r->headers_out.status = NGX_HTTP_INTERNAL_SERVER_ERROR;
        humha_process_kill(&p);
        humha_process_close(&p);
        goto output;
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
    ngx_table_elt_t * header;
    ngx_chain_t * cl;
    ngx_chain_t * body;
    ngx_buf_t * b;
    ngx_str_t method;
    size_t len = 0;
    ngx_uint_t idx;

    if (u->method.len) {
        method = u->method;
    }
    else {
        method = r->method_name;
    }

    len += method.len + 1
        + u->uri.len + 1
        + sizeof(ngx_http_humha_call_http_version) - 1
        + sizeof(CRLF) - 1;

    part = &r->headers_in.headers.part;

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
    if (cl != NULL) {
        return NGX_ERROR;
    }

    cl->buf = b;

    b->last = ngx_copy(b->last, method.data, method.len);
    *b->last++ = ' ';
    b->last = ngx_copy(b->last, r->upstream->uri.data, r->upstream->uri.len);
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

        b->last = ngx_copy(b->last, header[idx].key.data, header[idx].key.len);
        *b->last++ = ':';
        *b->last++ = ' ';
        b->last = ngx_copy(b->last, header[idx].value.data, header[idx].value.len);
        *b->last++ = CR;
        *b->last++ = LF;
    }
    *b->last++ = CR;
    *b->last++ = LF;

    u->request_bufs = cl;
    if (!r->request_body_no_buffering) {
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

}
