#ifndef _NGX_HTTP_HUMHA_PROMETHEUS_H
#define _NGX_HTTP_HUMHA_PROMETHEUS_H

#include <ngx_core.h>
#include "prometheus_metric_types.h"

typedef struct ngx_http_humha_prome_var_shm_s ngx_http_humha_prome_var_shm_t;
struct ngx_http_humha_prome_var_shm_s {
    prome_counter_t sync_exec_count;
    prome_counter_t async_exec_count;

    prome_histogram_t sync_exec_histogram;
    prome_histogram_t async_exec_histogram;

    prome_histogram_bucket_t sync_exec_histogram_bucket[11];
    prome_histogram_bucket_t async_exec_histogram_bucket[11];
};

ngx_int_t ngx_http_humha_prome_init_shm();

ngx_http_humha_prome_var_shm_t * ngx_http_humha_prome_get_shm();

void ngx_http_humha_prome_exec_count_inc(ngx_int_t is_async);

void ngx_http_humha_prome_exec_histogram_observer(ngx_int_t is_async, double val);

size_t ngx_http_humha_prome_serialize(ngx_pool_t * pool, ngx_chain_t * out);

#endif
