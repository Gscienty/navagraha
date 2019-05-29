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

typedef struct prome_histogram_bucket_s prome_histogram_bucket_t;
struct prome_histogram_bucket_s {
    prome_collect_list_t node;
    prome_notation_t notation;
    double le;
    double bucket;
};

#define prome_histogram_buckets_init(b, n, l) \
    ({ \
     prome_label_t * label = (prome_label_t *) malloc(sizeof(prome_label_t)); \
     if (label) { \
     prome_label_init(label, "le", #l); \
     prome_notation_init(&(b)->notation, n "_bucket"); \
     prome_notation_labels_append(&(b)->notation, label); \
     (b)->le = l; \
     (b)->bucket = 0.0F; \
     0; \
     } \
     -1; \
     })

typedef struct prome_histogram_s prome_histogram_t;
struct prome_histogram_s {
    prome_notation_t sum_notation;
    prome_notation_t count_notation;
    prome_collect_list_t buckets; /* stored prome_histogram_bucket_t */
    double sum_value;
    double count_value;
};

#define prome_histogram_init(h, n) \
    ({ \
     prome_notation_init(&(h)->sum_notation, n "_sum"); \
     prome_notation_init(&(h)->count_notation, n "_count"); \
     prome_collect_list_head_init(&(h)->buckets); \
     (h)->sum_value = 0.0F; \
     (h)->count_value = 0.0F; \
     0; \
     })

int prome_histogram_buckets_append(prome_histogram_t * histogram, prome_histogram_bucket_t * bucket);

int prome_histogram_observe(prome_histogram_t * histogram, double val);

typedef struct prome_summary_simple_s prome_summary_simple_t;
struct prome_summary_simple_s {
    prome_collect_list_t node;
    double simple_value;
};

int prome_summary_simple_init(prome_summary_simple_t * simple, double val);

typedef struct prome_summary_quantile_s prome_summary_quantile_t;
struct prome_summary_quantile_s {
    prome_collect_list_t node;
    prome_notation_t notation;
    double quantile;

    double calculated_simple;
};

#define prome_summary_quantile_init(q, n, z) \
    ({ \
     prome_label_t * label = (prome_label_t *) malloc(sizeof(prome_label_t)); \
     if (label) { \
     prome_label_init(label, "quantile", #z); \
     prome_collect_list_head_init(&(q)->node); \
     prome_notation_init(&(q)->notation, n); \
     prome_notation_labels_append(&(q)->notation, label); \
     (q)->quantile = z; \
     (q)->calculated_simple = 0.0F; \
     0; \
     } \
     -1; \
     })

typedef struct prome_summary_s prome_summary_t;
struct prome_summary_s {
    prome_notation_t sum_notation;
    prome_notation_t count_notation;

    prome_collect_list_t quantiles; /* stored prome_summary_quantile_t */
    prome_collect_list_t simples; /* stored prome_summary_simple_t */

    double sum_value;
    double count_value;
};

#define prome_summary_init(s, n) \
    ({ \
     prome_notation_init(&(s)->sum_notation, n); \
     prome_notation_init(&(s)->count_notation, n); \
     prome_collect_list_head_init(&(s)->simples); \
     (s)->sum_value = 0.0F; \
     (s)->count_value = 0.0F; \
     })

int prome_summary_observe(prome_summary_t * summary, double val);

int prome_summary_calculate(prome_summary_t * summary);

int prome_summary_reset(prome_summary_t * summary);

#endif
