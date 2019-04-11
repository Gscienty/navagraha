#include "kubeent/pod_condition.hpp"

namespace navagraha {
namespace kubeent {

char POD_CONDITION_LAST_PROBE_TIME[] = "lastProbeTime";
char POD_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char POD_CONDITION_MESSAGE[] = "message";
char POD_CONDITION_REASON[] = "reason";
char POD_CONDITION_STATUS[] = "status";
char POD_CONDITION_TYPE[] = "type";

void pod_condition::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->last_probe_time)
        .add(this->last_transition_time)
        .add(this->message)
        .add(this->reason)
        .add(this->status)
        .add(this->type);
}

}
}
