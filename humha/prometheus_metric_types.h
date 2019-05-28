#ifndef _PROMETHEUS_METRIC_TYPES_H
#define _PROMETHEUS_METRIC_TYPES_H

#include "prometheus_collections.h"

typedef struct prome_label_s prome_label_t;
struct prome_label_s {
    prome_collect_list_t node;

    const char * name;
    const char * value;
};

int prome_label_init(prome_label_t * label, const char * name, const char * value);

typedef struct prome_notation_s prome_notation_t;
struct prome_notation_s {
    const char * metric_name;
    prome_collect_list_t head; /* stored prome_label_t */
};

int prome_notation_init(prome_notation_t * notation, const char * metric_name);

int prome_notation_labels_append(prome_notation_t * notation, prome_label_t * label);

int prome_notation_serialize(prome_notation_t * notation, prome_buf_t * buf);

typedef struct prome_counter_s prome_counter_t;
struct prome_counter_s {
    prome_notation_t notation;

    double value;
};

int prome_counter_init(prome_counter_t * counter, const char * metric_name);

int prome_counter_inc(prome_counter_t * counter);

int prome_counter_add(prome_counter_t * counter, double val);

typedef struct prome_gauge_s prome_gauge_t;
struct prome_gauge_s {
    prome_notation_t notation;

    double value;
};

int prome_gauge_init(prome_gauge_t * gauge, const char * metric_name);

int prome_gauge_set(prome_gauge_t * gauge, double val);

int prome_gauge_inc(prome_gauge_t * gauge);

int prome_gauge_dec(prome_gauge_t * gauge);

int prome_gauge_add(prome_gauge_t * gauge, double val);

int prome_gauge_sub(prome_gauge_t * gauge, double val);

#endif
