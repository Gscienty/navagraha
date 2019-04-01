#include "kubeent/weighted_pod_affinity_term.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char WEIGHTED_POD_AFFINITY_TERM_POD_AFFINITY_TERM[] = "podAffinityTerm";
char WEIGHTED_POD_AFFINITY_TERM_WEIGHT[] = "weight";

void weighted_pod_affinity_term::serialize(weighted_pod_affinity_term & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.pod_affinity_term)
        .add(obj.weight)
        .serialize(str);
}

}
}
