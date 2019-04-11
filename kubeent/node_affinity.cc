#include "kubeent/node_affinity.hpp"

namespace navagraha {
namespace kubeent {

char NODE_AFFINITY_PREFERRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION[]
    = "preferredDuringSchedulingIgnoredDuringExecution";
char NODE_AFFINITY_REQUIRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION[]
    = "requiredDuringSchedulingIgnoredDuringExecution";

void node_affinity::bind(extensions::serializer_helper & helper)
{
    helper 
        .add(this->preferred_during_scheduling_ignored_during_execution)
        .add(this->required_during_scheduling_ignored_during_execution);
}

}
}
