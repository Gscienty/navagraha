#include "kubeent/daemon_set_condition.hpp"

namespace navagraha {
namespace kubeent {

char DAEMON_SET_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char DAEMON_SET_CONDITION_MESSAGE[] = "message";
char DAEMON_SET_CONDITION_REASON[] = "reason";
char DAEMON_SET_CONDITION_STATUS[] = "status";
char DAEMON_SET_CONDITION_TYPE[] = "type";

void daemon_set_condition::bind(extensions::serializer_helper & helper)
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
