#include "ngx_http_humha_conf.h"
#include "ngx_http_humha_prometheus.h"

ngx_int_t ngx_http_humha_prometheus_init_variables(ngx_conf_t * cf)
{
    (void) cf;

    return ngx_http_humha_prome_init_shm();
}

void * ngx_http_humha_create_loc_conf(ngx_conf_t * cf)
{
    ngx_http_humha_loc_conf_t * conf;
    ngx_uint_t args_idx;

    conf = (ngx_http_humha_loc_conf_t *) ngx_palloc(cf->pool, sizeof(ngx_http_humha_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }
    conf->prome.active = 0;

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

    conf->upstream.hide_headers = (ngx_array_t *) NGX_CONF_UNSET_PTR;
    conf->upstream.pass_headers = (ngx_array_t *) NGX_CONF_UNSET_PTR;

    return conf;
}
