#include "prometheus_metric_types.h"
#include <string.h>
#include <malloc.h>


/* notify: TODO check params and result */

int prome_label_init(prome_label_t * label, const char * name, const char * value)
{
    prome_collect_list_head_init(&label->node);
    label->name = name;
    label->value = value;

    return 0;
}

int prome_notation_init(prome_notation_t * notation, const char * metric_name)
{
    notation->metric_name = metric_name;
    prome_collect_list_head_init(&notation->head);

    return 0;
}

int prome_notation_labels_append(prome_notation_t * notation, prome_label_t * label)
{
    prome_collect_list_insert_prev(&notation->head, &label->node);

    return 0;
}

int prome_notation_serialize(prome_notation_t * notation, prome_buf_t * buf)
{
    size_t len = 0;
    size_t off = 0;
    int is_first = 1;
    prome_collect_list_t * label_node = NULL;

    len += strlen(notation->metric_name);

    if (prome_collect_list_is_empty(&notation->head)) {
        buf->len = len;
        buf->base = (char *) malloc(buf->len);
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
