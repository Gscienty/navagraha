#ifndef _PROMETHEUS_COLLECTIONS_H
#define _PROMETHEUS_COLLECTIONS_H

#include <stddef.h>

#define contain_of(p, t, m) ((t *) ((char *) (p) - (char *) &((t *) 0)->m))

typedef struct prome_collect_list_s prome_collect_list_t;
struct prome_collect_list_s {
    prome_collect_list_t * next;
    prome_collect_list_t * prev;
};

#define prome_collect_list_head_init(p) \
    ({ \
     (p)->next = (p); \
     (p)->prev = (p); \
     })

#define prome_collect_list_insert_prev(p, n) \
    ({ \
     (n)->next = (p); \
     (n)->prev = (p)->prev; \
     if ((p)->prev) (p)->prev->next = (n); \
     (p)->prev = (n); \
     })

#define prome_collect_list_insert_after(p, n) \
    ({ \
     (n)->prev = (p); \
     (n)->next = (p)->next; \
     if ((p)->next) (p)->next->prev = (n); \
     (p)->next = (n); \
     })

#define prome_collect_list_remove(p) \
    ({ \
     (p)->prev->next = (p)->next; \
     (p)->next->prev = (p)->prev; \
     })

#define prome_collect_list_is_empty(p) ((p)->next == (p))

typedef struct prome_buf_s prome_buf_t;
struct prome_buf_s {
    char * base;
    size_t len;
};

#define prome_buf_init(b) \
    ({ \
     (b)->base = NULL; \
     (b)->len = 0; \
     })

typedef struct prome_chain_s prome_chain_t;
struct prome_chain_s {
    prome_collect_list_t node;
    prome_buf_t buf;
};

size_t prome_chain_size(prome_collect_list_t * chain);

size_t prome_chain_count(prome_collect_list_t * chain);

int prome_chain_clear(prome_collect_list_t * chain);

#endif
