#include "ngx_http_apigw_loc_conf.h"
#include "ngx_http_apigw_handler.h"

static char * ngx_http_apigw_conf(ngx_conf_t * cf, ngx_command_t * cmd, void * conf);
static void * ngx_http_apigw_create_loc_conf(ngx_conf_t * cf);

static ngx_command_t ngx_http_apigw_module_commands[] = {
    {
        ngx_string("apigw_namespace"),
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
        ngx_http_apigw_conf,
        NGX_HTTP_LOC_CONF_OFFSET,
        0,
        NULL
    },

    ngx_null_command
};

static ngx_http_module_t ngx_http_apigw_module_ctx = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ngx_http_apigw_create_loc_conf,
    NULL
};

ngx_module_t ngx_http_apigw_module = {
    NGX_MODULE_V1,
    &ngx_http_apigw_module_ctx,
    ngx_http_apigw_module_commands,
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

static char * ngx_http_apigw_conf(ngx_conf_t * cf, ngx_command_t * cmd, void * conf)
{
    (void) cmd;
    ngx_http_core_loc_conf_t * ccf = (ngx_http_core_loc_conf_t *) ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    ngx_http_apigw_loc_conf_t * apigwcf = (ngx_http_apigw_loc_conf_t *) conf;
    ngx_str_t * conf_namespace = ((ngx_str_t *) cf->args->elts) + 1;
    char * env_namespace = getenv((const char *)conf_namespace->data);

    apigwcf->func_namespace.data = (u_char *) env_namespace;
    apigwcf->func_namespace.len = ngx_strlen(env_namespace);

    ccf->handler = ngx_http_apigw_handler;

    return NGX_CONF_OK;
}

static void * ngx_http_apigw_create_loc_conf(ngx_conf_t * cf)
{
    ngx_http_apigw_loc_conf_t * conf;

    conf = (ngx_http_apigw_loc_conf_t *) ngx_palloc(cf->pool, sizeof(ngx_http_apigw_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    conf->func_namespace.data = NULL;
    conf->func_namespace.len = 0;
    
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

    conf->upstream.hide_headers = (ngx_array_t *) NGX_CONF_UNSET_PTR;
    conf->upstream.pass_headers = (ngx_array_t *) NGX_CONF_UNSET_PTR;

    return conf;
}
