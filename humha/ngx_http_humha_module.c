#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include "humha_process.h"

#define NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT 16

typedef struct {
    ngx_str_t executor;
    ngx_str_t args[NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT];
} ngx_http_humha_loc_conf_t;

static char * ngx_http_humha(ngx_conf_t * cf, ngx_command_t * cmd, void * conf);
static ngx_int_t ngx_http_humha_handler(ngx_http_request_t * r);
static void * ngx_http_humha_create_loc_conf(ngx_conf_t * cf);
static void ngx_http_humha_readed_body_handler(ngx_http_request_t * r);
static ngx_int_t ngx_http_humha_process_input(ngx_http_request_t * r, humha_process_t * p);
static ngx_int_t ngx_http_humha_process_output(ngx_http_request_t * r, humha_process_t * p);

static ngx_command_t ngx_http_humha_module_commands[] = {
    {
        ngx_string("humha"),
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE3,
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
    conf->executor.data = NULL;
    conf->executor.len = 0;
    
    for (args_idx = 0; args_idx < 16; args_idx++) {
        conf->args->data = NULL;
        conf->args->len = 0;
    }

    return conf;
}


static char * ngx_http_humha(ngx_conf_t * cf, ngx_command_t * cmd, void * conf)
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

            args_delimiter = ngx_strchr(executor_executor_base, ' ');
            if (args_delimiter == NULL) {
                args_delimiter = executor_executor_base + ngx_strlen(executor_executor_base);
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
    return ngx_http_read_client_request_body(r, ngx_http_humha_readed_body_handler);
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
