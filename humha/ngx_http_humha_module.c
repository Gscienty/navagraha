#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include "humha_process.h"

#include <stdio.h>

typedef struct {
    ngx_str_t cmd;
} ngx_http_humha_loc_conf_t;

static char * ngx_http_humha(ngx_conf_t * cf, ngx_command_t * cmd, void * conf);
static ngx_int_t ngx_http_humha_handler(ngx_http_request_t * r);
static void * ngx_http_humha_create_loc_conf(ngx_conf_t * cf);

static ngx_command_t ngx_http_humha_module_commands[] = {
    {
        ngx_string("humha"),
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

    conf = ngx_palloc(cf->pool, sizeof(ngx_http_humha_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    return conf;
}


static char * ngx_http_humha(ngx_conf_t * cf, ngx_command_t * cmd, void * conf)
{
    (void) cmd;
    ngx_http_core_loc_conf_t * ccf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    ngx_http_humha_loc_conf_t * humha_conf = conf;
    ngx_str_t * value = cf->args->elts;

    humha_conf->cmd.data = value[1].data;
    humha_conf->cmd.len = value[1].len;

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
    ngx_http_humha_loc_conf_t * lcf;
    humha_process_t p;
    ngx_int_t retcode;
    ngx_int_t yield_size = 0;
    ngx_int_t remain_size = NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE;
    ngx_chain_t * out = ngx_alloc_chain_link(r->pool);
    ngx_chain_t * cur_chain = out;
    out->next = NULL;
    out->buf = ngx_create_temp_buf(r->pool, NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE);
    out->buf->last = out->buf->pos;
    out->buf->last_buf = 0;

    lcf = ngx_http_get_module_loc_conf(r, ngx_http_humha_module);
    if (lcf == NULL || lcf->cmd.data == NULL) {
        return NGX_DECLINED;
    }

    humha_process(lcf->cmd.data, &p);
    retcode = humha_process_wait(&p);

    if (retcode != 0) {
        r->headers_out.status = NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    else {
        r->headers_out.status = NGX_HTTP_OK;
    }

    r->headers_out.content_length_n = 0;
    ngx_str_set(&r->headers_out.content_type, "application/octet-stream");
    if (ngx_http_set_content_type(r) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    while ((yield_size = read(p.out, cur_chain->buf->pos + (NGX_HTTP_HUMHA_CHAIN_BLOCK_SIZE - remain_size), remain_size)) > 0) {
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
        return retcode;
    }

    retcode = ngx_http_output_filter(r, out);

    humha_process_close(&p);
    cur_chain = out;
    while ((cur_chain = ngx_chain_free_link(r->pool, cur_chain)) != NULL);
    
    return retcode;
}
