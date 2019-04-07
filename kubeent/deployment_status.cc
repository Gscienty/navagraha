#include "kubeent/deployment_status.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char DEPLOYMENT_STATUS_AVAILABLE_REPLICAS[] = "availableReplicas";
char DEPLOYMENT_STATUS_COLLISION_COUNT[] = "collisionCount";
char DEPLOYMENT_STATUS_CONDITIONS[] = "conditions";
char DEPLOYMENT_STATUS_OBSERVED_GENERATION[] = "observedGeneration";
char DEPLOYMENT_STATUS_READY_REPLICAS[] = "readyReplicas";
char DEPLOYMENT_STATUS_REPLICAS[] = "replicas";
char DEPLOYMENT_STATUS_UNAVAILABLE_REPLICAS[] = "unavailableReplicas";
char DEPLOYMENT_STATUS_UPDATED_REPLICAS[] = "updatedReplicas";

void deployment_status::serialize(deployment_status & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.available_replicas)
        .add(obj.collision_count)
        .add(obj.conditions)
        .add(obj.observed_generation)
        .add(obj.replicas)
        .add(obj.unavailable_replicas)
        .add(obj.updated_replicas)
        .serialize(str);
}
}
}
