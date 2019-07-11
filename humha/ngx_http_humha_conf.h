#ifndef _NGX_HTTP_HUMHA_CONF_H
#define _NGX_HTTP_HUMHA_CONF_H

#include <ngx_core.h>
#include <ngx_http.h>

#define NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT 16

typedef struct {
    ngx_int_t active;
} prome_conf;

typedef struct {
    ngx_http_upstream_conf_t upstream;
    ngx_str_t call_namespace;
    ngx_str_t executor;
    ngx_str_t args[NGX_HTTP_HUMHA_EXECUTOR_ARGS_MAX_COUNT];

    prome_conf prome;
} ngx_http_humha_loc_conf_t;

ngx_int_t ngx_http_humha_prometheus_init_variables(ngx_conf_t * cf);

void * ngx_http_humha_create_loc_conf(ngx_conf_t * cf);

#endif
