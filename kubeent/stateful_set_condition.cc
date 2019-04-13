#include "kubeent/stateful_set_condition.hpp"

namespace navagraha {
namespace kubeent {

char STATEFUL_SET_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char STATEFUL_SET_CONDITION_MESSAGE[] = "message";
char STATEFUL_SET_CONDITION_REASON[] = "reason";
char STATEFUL_SET_CONDITION_STATUS[] = "status";
char STATEFUL_SET_CONDITION_TYPE[] = "type";

void stateful_set_condition::bind(extensions::serializer_helper & helper)
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
