#include "kubeent/pod_affinity.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char POD_AFFINITY_PREFERRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION[]
    = "preferredDuringSchedulingIgnoredDuringExecution";
char POD_AFFINITY_REQUIRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION[]
    = "requiredDuringSchedulingIgnoredDuringExecution";

void pod_affinity::serialize(pod_affinity & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.preferred_during_scheduling_ignored_during_execution)
        .add(obj.required_during_scheduling_ignored_during_execution)
        .serialize(str);
}

}
}
