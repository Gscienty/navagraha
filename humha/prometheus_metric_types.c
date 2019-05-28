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
