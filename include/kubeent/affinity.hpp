#ifndef _NAVAGRAHA_KUBEENT_AFFINITY_H
#define _NAVAGRAHA_KUBEENT_AFFINITY_H

#include "extensions/field.hpp"
#include "kubeent/pod_affinity.hpp"
#include "kubeent/node_affinity.hpp"

namespace navagraha {
namespace kubeent {

extern char AFFINITY_NODE_AFFINITY[];
extern char AFFINITY_POD_AFFINITY[];
extern char AFFINITY_POD_ANTI_AFFINITY[];

class affinity {
public:
    extensions::field<
        node_affinity,
        AFFINITY_NODE_AFFINITY> node_affinity;
    extensions::field<
        pod_affinity,
        AFFINITY_POD_AFFINITY> pod_affinity_;
    extensions::field<
        pod_affinity,
        AFFINITY_POD_ANTI_AFFINITY> pod_anti_affinity;

    static void serialize(affinity & obj, std::ostringstream & str);
};

}
}

#endif
