#include "ngx_http_humha_prometheus.h"
#include <ngx_core.h>

static ngx_shm_t ngx_http_humha_prome_shm;

static void ngx_http_humha_prome_var_init()
{
    ngx_http_humha_prome_var_shm_t * var_p = ngx_http_humha_prome_get_shm();

    prome_counter_init(&var_p->sync_exec_count, "sync_exec_count");
    prome_counter_init(&var_p->async_exec_count, "async_exec_count");
}

ngx_int_t ngx_http_humha_prome_init_shm()
{
    ngx_int_t ret;

    ngx_http_humha_prome_shm.size = sizeof(ngx_http_humha_prome_var_shm_t);
    ret = ngx_shm_alloc(&ngx_http_humha_prome_shm);
    if (ret != NGX_OK) {
        return ret;
    }

    ngx_http_humha_prome_var_init();

    return NGX_OK;
}

void ngx_http_humha_prome_exec_count_inc(ngx_int_t is_async)
{
    ngx_http_humha_prome_var_shm_t * var_p = ngx_http_humha_prome_get_shm();
    if (var_p == NULL) {
        return;
    }

    if (is_async) {
        prome_counter_inc(&var_p->async_exec_count);
    }
    else {
        prome_counter_inc(&var_p->sync_exec_count);
    }
}
