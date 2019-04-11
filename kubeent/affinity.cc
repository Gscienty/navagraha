#include "kubeent/affinity.hpp"

namespace navagraha {
namespace kubeent {

char AFFINITY_NODE_AFFINITY[] = "nodeAffinity";
char AFFINITY_POD_AFFINITY[] = "podAffinity";
char AFFINITY_POD_ANTI_AFFINITY[] = "podAntiAffinity";

void affinity::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->node_affinity_)
        .add(this->pod_affinity_)
        .add(this->pod_anti_affinity);
}

}
}
