#ifndef _NGX_HTTP_HUMHA_PROMETHEUS_H
#define _NGX_HTTP_HUMHA_PROMETHEUS_H

#include <ngx_core.h>
#include "prometheus_metric_types.h"

typedef struct ngx_http_humha_prome_var_shm_s ngx_http_humha_prome_var_shm_t;
struct ngx_http_humha_prome_var_shm_s {
    prome_counter_t sync_exec_count;
    prome_counter_t async_exec_count;
};

ngx_int_t ngx_http_humha_prome_init_shm();

ngx_http_humha_prome_var_shm_t * ngx_http_humha_prome_get_shm();

void ngx_http_humha_prome_exec_count_inc(ngx_int_t is_async);

#endif
