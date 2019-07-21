#include "kubeent/horizontal_pod_autoscaler_status.hpp"

namespace navagraha {
namespace kubeent {

char HORIZONTAL_POD_AUTOSCALER_CURRENT_CPU_UTILIZATION_PERCENTAGE[] = "currentCPUUtilizationPercentage";
char HORIZONTAL_POD_AUTOSCALER_CURRENT_REPLICAS[] = "currentReplicas";
char HORIZONTAL_POD_AUTOSCALER_DESIRED_REPLICAS[] = "desiredReplicas";
char HORIZONTAL_POD_AUTOSCALER_LAST_SCALE_TIME[] = "lastScaleTime";
char HORIZONTAL_POD_AUTOSCALER_OBSERVED_GENERATION[] = "observedGeneration";

void horizontal_pod_autoscaler_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->current_cpu_utilization_percentage)
        .add(this->current_replicas)
        .add(this->desired_replicas)
        .add(this->last_scale_time)
        .add(this->observed_generation);
}

}
}
