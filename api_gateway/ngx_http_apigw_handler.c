#include "ngx_http_apigw_loc_conf.h"
#include "ngx_http_apigw_handler.h"

extern ngx_module_t ngx_http_apigw_module;

static ngx_int_t ngx_http_apigw_upstream_set_resolved(ngx_pool_t * pool, ngx_http_upstream_resolved_t * resolved, const char * uri);


ngx_int_t ngx_http_apigw_handler(ngx_http_request_t * r)
{
    ngx_http_upstream_t * u;
    ngx_http_apigw_loc_conf_t * loc_conf = (ngx_http_apigw_loc_conf_t *) ngx_http_get_module_loc_conf(r, ngx_http_apigw_module);
    ngx_str_t func_uri = { 0, NULL };
    size_t origin_urilen = r->uri_end - r->uri_start;

    if (ngx_http_upstream_create(r) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    u = r->upstream;
    u->conf = &loc_conf->upstream;
    u->output.tag = (ngx_buf_tag_t) &ngx_http_apigw_module;
    func_uri.len = origin_urilen + loc_conf->func_namespace.len;
    func_uri.data = (u_char *) ngx_palloc(r->pool, func_uri.len + 1);
    if (func_uri.data == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    ngx_memzero(func_uri.data, func_uri.len + 1);
    ngx_memcpy(func_uri.data, r->uri_start + 1, origin_urilen - 1);
    func_uri.data[origin_urilen - 1] = '.';
    ngx_memcpy(func_uri.data + origin_urilen, loc_conf->func_namespace.data, loc_conf->func_namespace.len);

    if (ngx_http_apigw_upstream_set_resolved(r->pool, u->resolved, (char *) func_uri.data) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    // TODO 

    return NGX_DONE;
}

static ngx_int_t ngx_http_apigw_upstream_set_resolved(ngx_pool_t * pool, ngx_http_upstream_resolved_t * resolved, const char * uri)
{
    struct sockaddr_in * func_sock = NULL;
    struct hostent * func_host = NULL;
    char * func_ipstr = NULL;

    func_sock = ngx_palloc(pool, sizeof(struct sockaddr_in));
    if (func_sock == NULL) {
        return NGX_ERROR;
    }

    resolved->sockaddr = (struct sockaddr *) func_sock;
    resolved->socklen = sizeof(*func_sock);
    resolved->naddrs = 1;
    resolved->port = 80;

    func_host = gethostbyname(uri);
    if (func_host == NULL) {
        return NGX_HTTP_NOT_FOUND;
    }

    func_sock->sin_family = AF_INET;
    func_sock->sin_port = htons((in_port_t) 80);
    func_ipstr = inet_ntoa(*(struct in_addr *) func_host->h_addr_list[0]);
    func_sock->sin_addr.s_addr = inet_addr(func_ipstr);

    return NGX_OK;
}
