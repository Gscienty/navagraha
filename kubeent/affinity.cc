#include "kubeent/affinity.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char AFFINITY_NODE_AFFINITY[] = "nodeAffinity";
char AFFINITY_POD_AFFINITY[] = "podAffinity";
char AFFINITY_POD_ANTI_AFFINITY[] = "podAntiAffinity";

void affinity::serialize(affinity & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.node_affinity)
        .add(obj.pod_affinity_)
        .add(obj.pod_anti_affinity)
        .serialize(str);
}

}
}
