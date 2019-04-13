#include "kubeent/stateful_set_status.hpp"

namespace navagraha {
namespace kubeent {

char STATEFUL_SET_STATUS_COLLISION_COUNT[] = "collisionCount";
char STATEFUL_SET_STATUS_CONDITIONS[] = "conditions";
char STATEFUL_SET_STATUS_CURRENT_REPLICAS[] = "currentReplicas";
char STATEFUL_SET_STATUS_CURRENT_REVISION[] = "currentRevision";
char STATEFUL_SET_STATUS_OBSERVED_GENERATION[] = "observedGeneration";
char STATEFUL_SET_STATUS_READY_REPLICAS[] = "readyReplicas";
char STATEFUL_SET_STATUS_REPLICAS[] = "replicas";
char STATEFUL_SET_STATUS_UPDATE_REVISION[] = "updateRevision";
char STATEFUL_SET_STATUS_UPDATE_REPLICAS[] = "updateReplicas";

void stateful_set_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->collision_count)
        .add(this->conditions)
        .add(this->current_replicas)
        .add(this->current_revision)
        .add(this->observed_generation)
        .add(this->ready_replicas)
        .add(this->replicas)
        .add(this->update_replicas)
        .add(this->update_revision);
}

}
}
