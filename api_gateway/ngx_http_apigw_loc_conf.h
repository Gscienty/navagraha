#ifndef _NGX_APIGW_LOC_CONF_H
#define _NGX_APIGW_LOC_CONF_H

#include <ngx_config.h>
#include <ngx_http.h>

typedef struct ngx_http_apigw_loc_conf_s ngx_http_apigw_loc_conf_t;
struct ngx_http_apigw_loc_conf_s {
    ngx_http_upstream_conf_t upstream;
    ngx_str_t func_namespace;
};

#endif
