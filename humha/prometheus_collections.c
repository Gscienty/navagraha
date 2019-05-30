#include "prometheus_collections.h"
#include <malloc.h>

size_t prome_chain_size(prome_collect_list_t * chain)
{
    size_t size = 0;
    prome_collect_list_t * p = NULL;
    prome_chain_t * pt = NULL;
    if (chain == NULL) {
        return 0;
    }

    for (p = chain->next; p != chain; p = p->next) {
        pt = contain_of(p, prome_chain_t, node);
        size += pt->buf.len;
    }

    return size;
}

int prome_chain_clear(prome_collect_list_t * chain)
{
    prome_chain_t * pt = NULL;
    if (chain == NULL) {
        return -1;
    }

    while (!prome_collect_list_is_empty(chain)) {
        pt = contain_of(chain->next, prome_chain_t, node);
        if (pt->buf.base) {
            free(pt->buf.base);
        }
        prome_collect_list_remove(chain->next);
        free(pt);
    }

    return 0;
}
