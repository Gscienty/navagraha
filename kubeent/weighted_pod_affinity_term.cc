#include "kubeent/weighted_pod_affinity_term.hpp"

namespace navagraha {
namespace kubeent {

char WEIGHTED_POD_AFFINITY_TERM_POD_AFFINITY_TERM[] = "podAffinityTerm";
char WEIGHTED_POD_AFFINITY_TERM_WEIGHT[] = "weight";

void weighted_pod_affinity_term::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->pod_affinity_term_)
        .add(this->weight);
}

}
}
