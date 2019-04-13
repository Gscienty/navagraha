#include "kubeent/replica_set_condition.hpp"

namespace navagraha {
namespace kubeent {

char REPLICA_SET_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char REPLICA_SET_CONDITION_MESSAGE[] = "message";
char REPLICA_SET_CONDITION_REASON[] = "reason";
char REPLICA_SET_CONDITION_STATUS[] = "status";
char REPLICA_SET_CONDITION_TYPE[] = "type";

void replica_set_condition::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->last_transition_time)
        .add(this->message)
        .add(this->reason)
        .add(this->status)
        .add(this->type);
}

}
}
