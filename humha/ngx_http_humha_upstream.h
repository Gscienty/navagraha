#ifndef _NGX_HTTP_HUMHA_UPSTREAM_H
#define _NGX_HTTP_HUMHA_UPSTREAM_H

#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_http_upstream.h>
#include "ngx_http_humha_conf.h"

typedef ngx_int_t (*ngx_http_humha_upstream_resolve_fptr_t) (ngx_pool_t *pool, ngx_http_upstream_resolved_t *, ngx_str_t * host);

ngx_int_t ngx_http_humha_upstream(ngx_http_request_t * r, ngx_http_humha_loc_conf_t * lcf, ngx_http_humha_upstream_resolve_fptr_t fptr);

#endif
