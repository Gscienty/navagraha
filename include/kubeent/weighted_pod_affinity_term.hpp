#ifndef _NAVAGRAHA_KUBEENT_WEIGHTED_POD_AFFINITY_TERM_H
#define _NAVAGRAHA_KUBEENT_WEIGHTED_POD_AFFINITY_TERM_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/pod_affinity_term.hpp"

namespace navagraha {
namespace kubeent {

extern char WEIGHTED_POD_AFFINITY_TERM_POD_AFFINITY_TERM[];
extern char WEIGHTED_POD_AFFINITY_TERM_WEIGHT[];

class weighted_pod_affinity_term : public extensions::serializable<weighted_pod_affinity_term> {
public:
    extensions::field<
        pod_affinity_term,
        WEIGHTED_POD_AFFINITY_TERM_POD_AFFINITY_TERM> pod_affinity_term_;
    extensions::field<
        int,
        WEIGHTED_POD_AFFINITY_TERM_WEIGHT> weight;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
