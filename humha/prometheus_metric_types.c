#include "prometheus_metric_types.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

int prome_label_init(prome_label_t * label, const char * name, const char * value)
{
    if (label == NULL) {
        return -1;
    }
    prome_collect_list_head_init(&label->node);
    label->name = name;
    label->value = value;

    return 0;
}

int prome_notation_init(prome_notation_t * notation, const char * metric_name)
{
    if (notation == NULL) {
        return -1;
    }
    notation->metric_name = metric_name;
    prome_collect_list_head_init(&notation->head);

    return 0;
}

int prome_notation_labels_append(prome_notation_t * notation, prome_label_t * label)
{
    if (notation == NULL || label == NULL) {
        return -1;
    }
    prome_collect_list_insert_prev(&notation->head, &label->node);

    return 0;
}

int prome_notation_serialize(prome_notation_t * notation, prome_buf_t * buf)
{
    size_t len = 0;
    size_t off = 0;
    int is_first = 1;
    prome_collect_list_t * label_node = NULL;

    if (notation == NULL || buf == NULL) {
        return -1;
    }

    len += strlen(notation->metric_name);

    if (prome_collect_list_is_empty(&notation->head)) {
        buf->len = len;
        buf->base = (char *) malloc(buf->len);
        if (buf->base == NULL) {
            return -2;
        }
        memcpy(buf->base, notation->metric_name, buf->len);
        return 0;
    }

    for (label_node = notation->head.next; label_node != &notation->head; label_node = label_node->next) {
        len += strlen(contain_of(label_node, prome_label_t, node)->name)
            + strlen(contain_of(label_node, prome_label_t, node)->value)
            + 5;
    }

    buf->len = len;
    buf->base = (char *) malloc(buf->len);
    if (buf->base == NULL) {
        return -2;
    }

    len = strlen(notation->metric_name);
    memcpy(buf->base, notation->metric_name, len);
    off += len;

    for (label_node = notation->head.next; label_node != &notation->head; label_node = label_node->next) {
        if (is_first) {
            memcpy(buf->base + off, "{", 1);
            off += 1;
            is_first = 0;
        }
        else {
            memcpy(buf->base + off, ", ", 2);
            off += 2;
        }

        len = strlen(contain_of(label_node, prome_label_t, node)->name);
        memcpy(buf->base + off, contain_of(label_node, prome_label_t, node)->name, len);
        off += len;

        memcpy(buf->base + off, "=\"", 2);
        off += 2;

        len = strlen(contain_of(label_node, prome_label_t, node)->value);
        memcpy(buf->base + off, contain_of(label_node, prome_label_t, node)->value, len);
        off += len;

        memcpy(buf->base + off, "\"", 1);
        off += 1;
    }
    memcpy(buf->base + off, "}", 1);
    return 0;
}

int prome_counter_init(prome_counter_t * counter, const char * metric_name)
{
    if (counter == NULL) {
        return -1;
    }

    counter->value = 0.0F;
    prome_notation_init(&counter->notation, metric_name);

    return 0;
}

int prome_counter_inc(prome_counter_t * counter)
{
    if (counter == NULL) {
        return -1;
    }
    counter->value += 1.0F;

    return 0;
}

int prome_counter_add(prome_counter_t * counter, double val)
{
    if (counter == NULL) {
        return -1;
    }
    if (val < 0) {
        return -2;
    }
    counter->value += val;

    return 0;
}

int prome_counter_serialize(prome_counter_t * counter, prome_collect_list_t * chain)
{
    prome_chain_t * notation_buf = NULL;
    prome_chain_t * num_buf = NULL;
    if (counter == NULL || chain == NULL) {
        return -1;
    }

    notation_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (notation_buf == NULL) {
        return -1;
    }
    num_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (num_buf == NULL) {
        free(notation_buf);
        return -1;
    }
    num_buf->buf.base = (char *) calloc(16, 1);
    if (num_buf->buf.base == NULL) {
        free(notation_buf);
        free(num_buf);
        return -1;
    }

    prome_notation_serialize(&counter->notation, &notation_buf->buf);
    num_buf->buf.len = sprintf(num_buf->buf.base, "%g", counter->value);

    prome_collect_list_insert_prev(chain, &notation_buf->node);
    prome_collect_list_insert_prev(chain, &num_buf->node);

    return 0;
}

int prome_gauge_init(prome_gauge_t * gauge, const char * metric_name)
{
    if (gauge == NULL) {
        return -1;
    }

    gauge->value = 0.0F;
    prome_notation_init(&gauge->notation, metric_name);

    return 0;
}

int prome_gauge_set(prome_gauge_t * gauge, double val)
{
    if (gauge == NULL) {
        return -1;
    }

    gauge->value = val;

    return 0;
}

int prome_gauge_inc(prome_gauge_t * gauge)
{
    if (gauge == NULL) {
        return -1;
    }

    gauge->value += 1.0F;

    return 0;
}

int prome_gauge_dec(prome_gauge_t * gauge)
{
    if (gauge == NULL) {
        return -1;
    }

    gauge->value -= 1.0F;

    return 0;
}

int prome_gauge_add(prome_gauge_t * gauge, double val)
{
    if (gauge == NULL) {
        return -1;
    }

    gauge->value += val;

    return 0;
}

int prome_gauge_sub(prome_gauge_t * gauge, double val)
{
    if (gauge == NULL) {
        return -1;
    }

    gauge->value -= val;

    return 0;
}

int prome_gauge_serialize(prome_gauge_t * gauge, prome_collect_list_t * chain)
{
    prome_chain_t * notation_buf = NULL;
    prome_chain_t * num_buf = NULL;
    if (gauge == NULL || chain == NULL) {
        return -1;
    }

    notation_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (notation_buf == NULL) {
        return -1;
    }
    prome_buf_init(&notation_buf->buf);

    num_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (num_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&num_buf->buf);

    num_buf->buf.base = (char *) calloc(16, 1);
    if (num_buf->buf.base == NULL) {
        goto malloc_error;
    }

    if (prome_notation_serialize(&gauge->notation, &notation_buf->buf)) {
        goto malloc_error;
    }
    num_buf->buf.len = sprintf(num_buf->buf.base, "%g", gauge->value);
    if (num_buf->buf.len <= 0) {
        goto malloc_error;
    }

    prome_collect_list_insert_prev(chain, &notation_buf->node);
    prome_collect_list_insert_prev(chain, &num_buf->node);

    return 0;

malloc_error:
    if (notation_buf != NULL) {
        if (notation_buf->buf.base != NULL) {
            free(notation_buf->buf.base);
        }
        free(notation_buf);
    }
    if (num_buf != NULL) {
        if (num_buf->buf.base != NULL) {
            free(num_buf->buf.base);
        }
        free(num_buf);
    }

    return -1;
}

int prome_histogram_buckets_append(prome_histogram_t * histogram, prome_histogram_bucket_t * bucket)
{
    if (histogram == NULL || bucket == NULL) {
        return -1;
    }

    prome_collect_list_insert_prev(&histogram->buckets, &bucket->node);

    return 0;
}

int prome_histogram_observe(prome_histogram_t * histogram, double val)
{
    prome_collect_list_t * p = NULL;
    prome_histogram_bucket_t * bucket = NULL;
    if (histogram == NULL) {
        return -1;
    }

    histogram->count_value += 1.0F;
    histogram->sum_value += val;

    for (p = histogram->buckets.next; p != &histogram->buckets; p = p->next) {
        bucket = contain_of(p, prome_histogram_bucket_t, node);
        if (val <= bucket->le) {
            bucket->bucket += 1.0F;
        }
    }
    histogram->inf_bucket.bucket += 1.0F;

    return 0;
}

int prome_histogram_serialize(prome_histogram_t * histogram, prome_collect_list_t * chain)
{
    prome_collect_list_t buckets_serialized;
    prome_collect_list_t * p = NULL;
    prome_histogram_bucket_t * bucket = NULL;
    prome_chain_t * pt = NULL;
    prome_chain_t * sum_notation_buf = NULL;
    prome_chain_t * sum_buf = NULL;
    prome_chain_t * count_notation_buf = NULL;
    prome_chain_t * count_buf = NULL;
    prome_chain_t * inf_notation_buf = NULL;
    prome_chain_t * inf_buf = NULL;
    char tmp_double_val[16] = { 0 };

    if (histogram == NULL || chain == NULL) {
        return -1;
    }
    prome_collect_list_head_init(&buckets_serialized);

    sum_notation_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (sum_notation_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&sum_notation_buf->buf);

    sum_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (sum_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&sum_buf->buf);
    sum_buf->buf.base = (char *) calloc(16, 1);
    if (sum_buf->buf.base == NULL) {
        goto malloc_error;
    }

    count_notation_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (count_notation_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&count_notation_buf->buf);

    count_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (count_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&count_buf->buf);
    count_buf->buf.base = (char *) calloc(16, 1);
    if (count_buf->buf.base == NULL) {
        goto malloc_error;
    }

    inf_notation_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (inf_notation_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&inf_notation_buf->buf);

    inf_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (inf_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&inf_buf->buf);
    inf_buf->buf.base = (char *) calloc(16, 1);
    if (inf_buf->buf.base == NULL) {
        goto malloc_error;
    }

    if (prome_notation_serialize(&histogram->sum_notation, &sum_notation_buf->buf) < 0) {
        goto malloc_error;
    }
    if (prome_notation_serialize(&histogram->count_notation, &count_notation_buf->buf) < 0) {
        goto malloc_error;
    }
    sum_buf->buf.len = sprintf(sum_buf->buf.base, "%g", histogram->sum_value);
    if (sum_buf->buf.len <= 0) {
        goto malloc_error;
    }
    count_buf->buf.len = sprintf(sum_buf->buf.base, "%g", histogram->count_value);
    if (count_buf->buf.len <= 0) {
        goto malloc_error;
    }

    prome_collect_list_insert_prev(chain, &count_notation_buf->node);
    prome_collect_list_insert_prev(chain, &count_buf->node);
    prome_collect_list_insert_prev(chain, &sum_notation_buf->node);
    prome_collect_list_insert_prev(chain, &sum_buf->node);

    for (p = histogram->buckets.next; p != &histogram->buckets; p = p->next) {
        bucket = contain_of(p, prome_histogram_bucket_t, node);
        pt = (prome_chain_t *) malloc(sizeof(prome_chain_t));
        if (pt == NULL) {
            goto malloc_error;
        }
        prome_buf_init(&pt->buf);
        if (prome_notation_serialize(&bucket->notation, &pt->buf) < 0) {
            free(pt);
            goto malloc_error;
        }
        prome_collect_list_insert_prev(chain, &pt->node);

        pt = (prome_chain_t *) malloc(sizeof(prome_chain_t));
        if (pt == NULL) {
            goto malloc_error;
        }
        prome_buf_init(&pt->buf);
        pt->buf.base = (char *) calloc(16, 1);
        if (pt->buf.base != NULL) {
            free(pt);
            goto malloc_error;
        }
        pt->buf.len = sprintf(tmp_double_val, "%g", bucket->bucket);
        if (pt->buf.len <= 0) {
            free(pt->buf.base);
            free(pt);
            goto malloc_error;
        }
        memcpy(pt->buf.base, tmp_double_val, pt->buf.len);
        prome_collect_list_insert_prev(chain, &pt->node);
    }

    chain->prev->next = buckets_serialized.next;
    buckets_serialized.next->prev = chain->prev;
    chain->prev = buckets_serialized.prev;
    buckets_serialized.prev->next = chain;

    return 0;

malloc_error:
    if (sum_notation_buf != NULL) {
        if (sum_notation_buf->buf.base != NULL) {
            free(sum_notation_buf->buf.base);
        }
        free(sum_notation_buf);
    }
    if (sum_buf != NULL) {
        if (sum_buf->buf.base != NULL) {
            free(sum_buf->buf.base);
        }
        free(sum_buf);
    }
    if (count_notation_buf != NULL) {
        if (count_notation_buf->buf.base != NULL) {
            free(count_notation_buf->buf.base);
        }
        free(count_notation_buf);
    }
    if (count_buf != NULL) {
        if (count_buf->buf.base != NULL) {
            free(count_buf->buf.base);
        }
        free(count_buf);
    }
    if (inf_notation_buf != NULL) {
        if (inf_notation_buf->buf.base != NULL) {
            free(inf_notation_buf->buf.base);
        }
        free(inf_notation_buf);
    }
    if (inf_buf != NULL) {
        if (inf_buf->buf.base != NULL) {
            free(inf_buf->buf.base);
        }
        free(inf_buf);
    }
    while (!prome_collect_list_is_empty(&buckets_serialized)) {
        pt = contain_of(buckets_serialized.next, prome_chain_t, node);
        if (pt->buf.base != NULL) {
            free(pt->buf.base);
        }
        prome_collect_list_remove(buckets_serialized.next);
        free(pt);
    }
    return -1;
}

int prome_summary_simple_init(prome_summary_simple_t * simple, double val)
{
    if (simple == NULL) {
        return -1;
    }

    prome_collect_list_head_init(&simple->node);
    simple->simple_value = val;

    return 0;
}

int prome_summary_observe(prome_summary_t * summary, double val)
{
    prome_summary_simple_t * simple = NULL;
    prome_collect_list_t * p = NULL;
    prome_summary_simple_t * refer_simple = NULL;
    int inserted_flag = 0;
    if (summary == NULL) {
        return -1;
    }

    simple = (prome_summary_simple_t *) malloc(sizeof(prome_summary_simple_t));
    if (simple == NULL) {
        return -1;
    }
    prome_summary_simple_init(simple, val);

    summary->count_value += 1.0F;
    summary->sum_value += val;

    for (p = summary->simples.next; p != &summary->simples; p = p->next) {
        refer_simple = contain_of(p, prome_summary_simple_t, node);

        if (simple->simple_value <= refer_simple->simple_value) {
            inserted_flag = 1;
            prome_collect_list_insert_prev(&refer_simple->node, &simple->node);
        }
    }

    if (inserted_flag == 0) {
        prome_collect_list_insert_prev(&summary->simples, &simple->node);
    }

    return 0;
}

int prome_summary_calculate(prome_summary_t * summary)
{
    prome_collect_list_t * quantile_p = NULL;
    prome_summary_quantile_t * quantile = NULL;
    prome_collect_list_t * simple_p = NULL;
    prome_summary_simple_t * simple = NULL;
    int target_nth = 0;
    int cur_nth = 0;

    if (summary == NULL) {
        return -1;
    }

    for (quantile_p = summary->quantiles.next; quantile_p != &summary->quantiles; quantile_p = quantile_p->next) {
        quantile = contain_of(quantile_p, prome_summary_quantile_t, node);
        target_nth = summary->count_value * quantile->quantile;
        cur_nth = 0;

        quantile->calculated_simple = 0;
        for (simple_p = summary->simples.next; simple_p != &summary->simples; simple_p = simple_p->next) {
            cur_nth++;
            if (cur_nth == target_nth) {
                simple = contain_of(simple_p, prome_summary_simple_t, node);
                quantile->calculated_simple = simple->simple_value;
                break;
            }
        }
    }

    return 0;
}

int prome_summary_reset(prome_summary_t * summary)
{
    prome_summary_simple_t * simple;
    if (summary == NULL) {
        return -1;
    }

    while (!prome_collect_list_is_empty(&summary->simples)) {
        simple = contain_of(summary->simples.next, prome_summary_simple_t, node);
        prome_collect_list_remove(&simple->node);
        free(simple);
    }

    summary->count_value = 0.0F;
    summary->sum_value = 0.0F;

    return 0;
}

int prome_summary_serialize(prome_summary_t * summary, prome_collect_list_t * chain)
{
    prome_collect_list_t quantiles_serialized;
    prome_collect_list_t * p = NULL;
    prome_summary_quantile_t * quantile = NULL;
    prome_chain_t * sum_notation_buf = NULL;
    prome_chain_t * count_notation_buf = NULL;
    prome_chain_t * sum_num_buf = NULL;
    prome_chain_t * count_num_buf = NULL;
    prome_chain_t * pt = NULL;
    char tmp_double_val[16] = { 0 };
    if (summary == NULL || chain == NULL) {
        return -1;
    }
    prome_collect_list_head_init(&quantiles_serialized);

    sum_notation_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (sum_notation_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&sum_notation_buf->buf);

    sum_num_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (sum_num_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&sum_num_buf->buf);
    sum_num_buf->buf.base = (char *) calloc(16, 1);
    if (sum_num_buf->buf.base == NULL) {
        goto malloc_error;
    }

    count_notation_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (count_notation_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&count_notation_buf->buf);

    count_num_buf = (prome_chain_t *) malloc(sizeof(prome_chain_t));
    if (count_num_buf == NULL) {
        goto malloc_error;
    }
    prome_buf_init(&count_num_buf->buf);
    count_num_buf->buf.base = (char *) calloc(16, 1);
    if (count_num_buf->buf.base == NULL) {
        goto malloc_error;
    }

    if (prome_notation_serialize(&summary->count_notation, &count_notation_buf->buf) < 0) {
        goto malloc_error;
    }
    if (prome_notation_serialize(&summary->sum_notation, &sum_notation_buf->buf) < 0) {
        goto malloc_error;
    }
    sum_num_buf->buf.len = sprintf(sum_num_buf->buf.base, "%g", summary->sum_value);
    if (sum_num_buf->buf.len <= 0) {
        goto malloc_error;
    }
    count_num_buf->buf.len = sprintf(count_num_buf->buf.base, "%g", summary->count_value);
    if (count_num_buf->buf.len <= 0) {
        goto malloc_error;
    }

    prome_collect_list_insert_prev(chain, &count_notation_buf->node);
    prome_collect_list_insert_prev(chain, &count_num_buf->node);
    prome_collect_list_insert_prev(chain, &sum_notation_buf->node);
    prome_collect_list_insert_prev(chain, &sum_num_buf->node);

    for (p = summary->quantiles.next; p != &summary->quantiles; p = p->next) {
        quantile = contain_of(p, prome_summary_quantile_t, node);
        pt = (prome_chain_t *) malloc(sizeof(prome_chain_t));
        if (pt == NULL) {
            goto malloc_error;
        }
        prome_buf_init(&pt->buf);
        if (prome_notation_serialize(&quantile->notation, &pt->buf) < 0) {
            free(pt);
            goto malloc_error;
        }
        prome_collect_list_insert_prev(chain, &pt->node);

        pt = (prome_chain_t *) malloc(sizeof(prome_chain_t));
        if (pt == NULL) {
            goto malloc_error;
        }
        prome_buf_init(&pt->buf);
        pt->buf.base = (char *) calloc(16, 1);
        if (pt->buf.base != NULL) {
            free(pt);
            goto malloc_error;
        }
        pt->buf.len = sprintf(tmp_double_val, "%g", quantile->calculated_simple);
        if (pt->buf.len <= 0) {
            free(pt->buf.base);
            free(pt);
            goto malloc_error;
        }
        memcpy(pt->buf.base, tmp_double_val, pt->buf.len);
        prome_collect_list_insert_prev(chain, &pt->node);
    }

    chain->prev->next = quantiles_serialized.next;
    quantiles_serialized.next->prev = chain->prev;
    chain->prev = quantiles_serialized.prev;
    quantiles_serialized.prev->next = chain;

    return 0;

malloc_error:
    if (sum_notation_buf != NULL) {
        if (sum_notation_buf->buf.base != NULL) {
            free(sum_notation_buf->buf.base);
        }
        free(sum_notation_buf);
    }
    if (count_notation_buf->buf.base != NULL) {
        if (count_notation_buf->buf.base != NULL) {
            free(count_notation_buf->buf.base);
        }
        free(count_notation_buf);
    }
    if (sum_num_buf != NULL) {
        if (sum_num_buf->buf.base != NULL) {
            free(sum_num_buf->buf.base);
        }
        free(sum_num_buf);
    }
    if (count_num_buf != NULL) {
        if (count_num_buf->buf.base != NULL) {
            free(count_num_buf->buf.base);
        }
        free(count_num_buf);
    }
    while (!prome_collect_list_is_empty(&quantiles_serialized)) {
        pt = contain_of(quantiles_serialized.next, prome_chain_t, node);
        if (pt->buf.base != NULL) {
            free(pt->buf.base);
        }
        prome_collect_list_remove(quantiles_serialized.next);
        free(pt);
    }
    return -1;
}
