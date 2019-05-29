#include "prometheus_metric_types.h"
#include <string.h>
#include <malloc.h>

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

    return 0;
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
