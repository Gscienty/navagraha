#ifndef _NAVAGRAHA_KUBEENT_AFFINITY_H
#define _NAVAGRAHA_KUBEENT_AFFINITY_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/pod_affinity.hpp"
#include "kubeent/node_affinity.hpp"

namespace navagraha {
namespace kubeent {

extern char AFFINITY_NODE_AFFINITY[];
extern char AFFINITY_POD_AFFINITY[];
extern char AFFINITY_POD_ANTI_AFFINITY[];

class affinity : public serializable<affinity> {
public:
    extensions::field<
        node_affinity,
        AFFINITY_NODE_AFFINITY> node_affinity_;
    extensions::field<
        pod_affinity,
        AFFINITY_POD_AFFINITY> pod_affinity_;
    extensions::field<
        pod_affinity,
        AFFINITY_POD_ANTI_AFFINITY> pod_anti_affinity;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
