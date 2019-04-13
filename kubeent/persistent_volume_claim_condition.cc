#include "kubeent/persistent_volume_claim_condition.hpp"

namespace navagraha {
namespace kubeent {

char PERSISTENT_VOLUME_CLAIM_CONDITION_LAST_PROBE_TIME[] = "lastProbeTime";
char PERSISTENT_VOLUME_CLAIM_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char PERSISTENT_VOLUME_CLAIM_CONDITION_MESSAGE[] = "message";
char PERSISTENT_VOLUME_CLAIM_CONDITION_REASON[] = "reason";
char PERSISTENT_VOLUME_CLAIM_CONDITION_STATUS[] = "status";
char PERSISTENT_VOLUME_CLAIM_CONDITION_TYPE[] = "type";

void persistent_volume_claim_condition::bind(extensions::serializer_helper & helper)
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
