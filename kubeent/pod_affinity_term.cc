#include "kubeent/pod_affinity_term.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char POD_AFFINITY_TERM_LABEL_SELECTOR[] = "labelSelector";
char POD_AFFINITY_NAMESPACES[] = "namespaces";
char POD_AFFINITY_TOPOLOGY_KEY[] = "topologyKey";

void pod_affinity_term::serialize(pod_affinity_term & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.label_selector)
        .add(obj.namespaces)
        .add(obj.topology_key)
        .serialize(str);
}

}
}
