#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

#include <stdio.h>

typedef struct {
    ngx_str_t cmd;
} ngx_http_humha_loc_conf_t;

static char * ngx_http_humha(ngx_conf_t * cf, ngx_command_t * cmd, void * conf);
static ngx_int_t ngx_http_humha_handler(ngx_http_request_t * r);
static void * ngx_http_humha_create_loc_conf(ngx_conf_t * cf);
static ngx_int_t ngx_http_humha_init(ngx_conf_t * cf);

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
    ngx_http_humha_init, // postconfiguration
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

static ngx_int_t ngx_http_humha_init(ngx_conf_t * cf)
{
    ngx_http_core_loc_conf_t * lcf;
    lcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    lcf->handler = ngx_http_humha_handler;

    return NGX_OK;
}

static char * ngx_http_humha(ngx_conf_t * cf, ngx_command_t * cmd, void * conf)
{
    (void) cmd;
    ngx_http_humha_loc_conf_t * humha_conf = conf;
    ngx_str_t * value = cf->args->elts;

    humha_conf->cmd.data = value->data;
    humha_conf->cmd.len = value->len;

    return NGX_CONF_OK;
}

static ngx_int_t ngx_http_humha_handler(ngx_http_request_t * r)
{

    return NGX_OK;
}
