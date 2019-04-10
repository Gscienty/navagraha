#include "kubeent/deployment_status.hpp"

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

void deployment_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->available_replicas)
        .add(this->collision_count)
        .add(this->conditions)
        .add(this->observed_generation)
        .add(this->ready_replicas)
        .add(this->replicas)
        .add(this->unavailable_replicas)
        .add(this->updated_replicas);
}
}
}
