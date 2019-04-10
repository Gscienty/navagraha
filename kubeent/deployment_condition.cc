#include "kubeent/deployment_condition.hpp"

namespace navagraha {
namespace kubeent {

char DEPLOYMENT_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char DEPLOYMENT_CONDITION_LAST_UPDATE_TIME[] = "lastUpdateTime";
char DEPLOYMENT_CONDITION_MESSAGE[] = "message";
char DEPLOYMENT_CONDITION_STATUS[] = "status";
char DEPLOYMENT_CONDITION_TYPE[] = "type";

void deployment_condition::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->last_transition_time)
        .add(this->last_update_time)
        .add(this->message)
        .add(this->status)
        .add(this->type);
}
}
}
