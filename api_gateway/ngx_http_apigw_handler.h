#ifndef _NGX_HTTP_APIGW_HANDLER_H
#define _NGX_HTTP_APIGW_HANDLER_H

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

typedef struct ngx_http_apigw_ctx_s ngx_http_apigw_ctx_t;
struct ngx_http_apigw_ctx_s {
    ngx_str_t func_host;
};

ngx_int_t ngx_http_apigw_handler(ngx_http_request_t * r);

#endif
