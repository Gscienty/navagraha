#include "kubeent/node_condition.hpp"

namespace navagraha {
namespace kubeent {

char NODE_CONDITION_LAST_HEARTBEAT_TIME[] = "lastHeartbeatTime";
char NODE_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char NODE_CONDITION_MESSAGE[] = "message";
char NODE_CONDITION_REASON[] = "reason";
char NODE_CONDITION_STATUS[] = "status";
char NODE_CONDITION_TYPE[] = "type";

void node_condition::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->last_heartbeat_time)
        .add(this->last_transition_time)
        .add(this->message)
        .add(this->reason)
        .add(this->status)
        .add(this->type);
}

}
}
