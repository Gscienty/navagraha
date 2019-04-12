#include "kubeent/job_condition.hpp"

namespace navagraha {
namespace kubeent {

char JOB_CONDITION_LAST_PROBE_TIME[] = "lastProbeTime";
char JOB_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char JOB_CONDITION_MESSAGE[] = "message";
char JOB_CONDITION_REASON[] = "reason";
char JOB_CONDITION_STATUS[] = "status";
char JOB_CONDITION_TYPE[] = "type";

void job_condition::bind(extensions::serializer_helper & helper)
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
