#include "kubeent/replication_controller_status.hpp"

namespace navagraha {
namespace kubeent {

char REPLICATION_CONTROLLER_STATUS_AVAILABLE_REPLICAS[] = "availableReplicas";
char REPLICATION_CONTROLLER_STATUS_CONDITIONS[] = "conditions";
char REPLICATION_CONTROLLER_STATUS_FULLY_LABELED_REPLICAS[] = "fullyLabeledReplicas";
char REPLICATION_CONTROLLER_STATUS_OBSERVED_GENERATION[] = "observedGeneration";
char REPLICATION_CONTROLLER_STATUS_READY_REPLICAS[] = "readyReplicas";
char REPLICATION_CONTROLLER_STATUS_REPLICAS[] = "replicas";

void replication_controller_status::bind(extensions::serializer_helper & helper)
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
