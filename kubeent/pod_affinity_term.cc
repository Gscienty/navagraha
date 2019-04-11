#include "kubeent/pod_affinity_term.hpp"

namespace navagraha {
namespace kubeent {

char POD_AFFINITY_TERM_LABEL_SELECTOR[] = "labelSelector";
char POD_AFFINITY_NAMESPACES[] = "namespaces";
char POD_AFFINITY_TOPOLOGY_KEY[] = "topologyKey";

void pod_affinity_term::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->label_selector_)
        .add(this->namespaces)
        .add(this->topology_key);
}

}
}
