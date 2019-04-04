#include "kubeent/deployment_condition.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char DEPLOYMENT_CONDITION_LAST_TRANSITION_TIME[] = "lastTransitionTime";
char DEPLOYMENT_CONDITION_LAST_UPDATE_TIME[] = "lastUpdateTime";
char DEPLOYMENT_CONDITION_MESSAGE[] = "message";
char DEPLOYMENT_CONDITION_STATUS[] = "status";
char DEPLOYMENT_CONDITION_TYPE[] = "type";

void deployment_condition::serialize(deployment_condition & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.last_transition_time)
        .add(obj.last_update_time)
        .add(obj.message)
        .add(obj.status)
        .add(obj.type)
        .serialize(str);
}
}
}
