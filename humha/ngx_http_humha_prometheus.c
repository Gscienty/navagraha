#include "ngx_http_humha_prometheus.h"
#include <ngx_core.h>

static ngx_shm_t ngx_http_humha_prome_shm;

static void ngx_http_humha_prome_var_init()
{
    ngx_int_t i;
    ngx_http_humha_prome_var_shm_t * var_p = ngx_http_humha_prome_get_shm();

    prome_counter_init(&var_p->sync_exec_count, "sync_exec_count");
    prome_counter_init(&var_p->async_exec_count, "async_exec_count");

    prome_histogram_init(&var_p->sync_exec_histogram, "sync_exec_histogram");
    prome_histogram_init(&var_p->async_exec_histogram, "async_exec_histogram");

    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[0], "sync_exec_histogram", 0.005);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[1], "sync_exec_histogram", 0.01);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[2], "sync_exec_histogram", 0.025);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[3], "sync_exec_histogram", 0.05);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[4], "sync_exec_histogram", 0.1);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[5], "sync_exec_histogram", 0.25);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[6], "sync_exec_histogram", 0.5);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[7], "sync_exec_histogram", 1);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[8], "sync_exec_histogram", 2.5);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[9], "sync_exec_histogram", 5);
    prome_histogram_buckets_init(&var_p->sync_exec_histogram_bucket[10], "sync_exec_histogram", 10);

    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[0], "async_exec_histogram", 0.005);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[1], "async_exec_histogram", 0.01);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[2], "async_exec_histogram", 0.025);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[3], "async_exec_histogram", 0.05);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[4], "async_exec_histogram", 0.1);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[5], "async_exec_histogram", 0.25);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[6], "async_exec_histogram", 0.5);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[7], "async_exec_histogram", 1);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[8], "async_exec_histogram", 2.5);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[9], "async_exec_histogram", 5);
    prome_histogram_buckets_init(&var_p->async_exec_histogram_bucket[10], "async_exec_histogram", 10);

    for (i = 0; i < 11; i++) {
        prome_histogram_buckets_append(&var_p->sync_exec_histogram, &var_p->sync_exec_histogram_bucket[i]);
        prome_histogram_buckets_append(&var_p->async_exec_histogram, &var_p->async_exec_histogram_bucket[i]);
    }
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

ngx_http_humha_prome_var_shm_t * ngx_http_humha_prome_get_shm()
{
    return (ngx_http_humha_prome_var_shm_t *) ngx_http_humha_prome_shm.addr;
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

void ngx_http_humha_prome_exec_histogram_observer(ngx_int_t is_async, double val)
{
    ngx_http_humha_prome_var_shm_t * var_p = ngx_http_humha_prome_get_shm();
    if (var_p == NULL) {
        return;
    }

    if (is_async) {
        prome_histogram_observe(&var_p->async_exec_histogram, val);
    }
    else {
        prome_histogram_observe(&var_p->sync_exec_histogram, val);
    }
}

size_t ngx_http_humha_prome_serialize(ngx_pool_t * pool, ngx_chain_t * out)
{
    size_t size = 0;
    prome_collect_list_t chain;
    ngx_http_humha_prome_var_shm_t * var_p = ngx_http_humha_prome_get_shm();
    prome_chain_t * pt = NULL;
    ngx_int_t odd_flag = 0;

    prome_collect_list_head_init(&chain);
    prome_counter_serialize(&var_p->sync_exec_count, &chain);
    prome_counter_serialize(&var_p->async_exec_count, &chain);
    prome_histogram_serialize(&var_p->sync_exec_histogram, &chain);
    prome_histogram_serialize(&var_p->async_exec_histogram, &chain);

    size = prome_chain_size(&chain) + prome_chain_count(&chain);

    out->buf = ngx_create_temp_buf(pool, size);
    out->buf->last = out->buf->pos;
    out->buf->last_buf = 1;

    while (!prome_collect_list_is_empty(&chain)) {
        pt = contain_of(chain.next, prome_chain_t, node);

        ngx_memcpy(out->buf->last, pt->buf.base, pt->buf.len);
        out->buf->last += pt->buf.len;
        *out->buf->last++ = (odd_flag ^= 1) ? ' ' : '\n';
        free(pt->buf.base);
        prome_collect_list_remove(chain.next);
        free(pt);
    }

    return size;
}
