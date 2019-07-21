#include "kubeent/horizontal_pod_autoscaler_spec.hpp"

namespace navagraha {
namespace kubeent {

char HORIZONTAL_POD_AUTOSCALER_SPEC_MAX_REPLICAS[] = "maxReplicas";
char HORIZONTAL_POD_AUTOSCALER_SPEC_MIN_REPLICAS[] = "minReplicas";
char HORIZONTAL_POD_AUTOSCALER_SPEC_SCALE_TARGET_REF[] = "scaleTargetRef";
char HORIZONTAL_POD_AUTOSCALER_SPEC_TARGET_CPU_UTILIZATION_PERCENTAGE[] = "CPUUtilizationPercentage";

void horizontal_pod_autoscaler_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->max_replicas)
        .add(this->min_replicas)
        .add(this->scale_target_ref)
        .add(this->cpu_utilization_percentage);
}

}
}
