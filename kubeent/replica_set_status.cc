#include "kubeent/replica_set_status.hpp"

namespace navagraha {
namespace kubeent {

char REPLICA_SET_STATUS_AVAILABLE_REPLICAS[] = "availableReplicas";
char REPLICA_SET_STATUS_CONDITIONS[] = "conditions";
char REPLICA_SET_STATUS_FULLY_LABELED_REPLICAS[] = "fullyLabeledReplicas";
char REPLICA_SET_STATUS_OBSERVED_GENERATION[] = "observedGeneration";
char REPLICA_SET_STATUS_READY_REPLICAS[] = "readyReplicas";
char REPLICA_SET_STATUS_REPLICAS[] = "replicas";

void replica_set_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->available_replicas)
        .add(this->conditions)
        .add(this->fully_labeled_replicas)
        .add(this->observed_generation)
        .add(this->ready_replicas)
        .add(this->replicas);
}

}
}
