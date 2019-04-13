#include "kubeent/replication_controller_condition.hpp"

namespace navagraha {
namespace kubeent {

char REPLICATION_CONTROLLER_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char REPLICATION_CONTROLLER_CONDITION_MESSAGE[] = "message";
char REPLICATION_CONTROLLER_CONDITION_REASON[] = "reason";
char REPLICATION_CONTROLLER_CONDITION_STATUS[] = "status";
char REPLICATION_CONTROLLER_CONDITION_TYPE[] = "type";

void replication_controller_condition::bind(extensions::serializer_helper & helper)
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
