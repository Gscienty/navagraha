#ifndef _NAVAGRAHA_KUBEENT_HORIZONTAL_POD_AUTOSCALER_STATUS_H
#define _NAVAGRAHA_KUBEENT_HORIZONTAL_POD_AUTOSCALER_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializable.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/time.hpp"

namespace navagraha {
namespace kubeent {

extern char HORIZONTAL_POD_AUTOSCALER_CURRENT_CPU_UTILIZATION_PERCENTAGE[];
extern char HORIZONTAL_POD_AUTOSCALER_CURRENT_REPLICAS[];
extern char HORIZONTAL_POD_AUTOSCALER_DESIRED_REPLICAS[];
extern char HORIZONTAL_POD_AUTOSCALER_LAST_SCALE_TIME[];
extern char HORIZONTAL_POD_AUTOSCALER_OBSERVED_GENERATION[];

class horizontal_pod_autoscaler_status : public extensions::serializable<horizontal_pod_autoscaler_status> {
public:
    extensions::field<int, HORIZONTAL_POD_AUTOSCALER_CURRENT_CPU_UTILIZATION_PERCENTAGE> current_cpu_utilization_percentage;
    extensions::field<int, HORIZONTAL_POD_AUTOSCALER_CURRENT_REPLICAS> current_replicas;
    extensions::field<int, HORIZONTAL_POD_AUTOSCALER_DESIRED_REPLICAS> desired_replicas;
    extensions::field<time, HORIZONTAL_POD_AUTOSCALER_LAST_SCALE_TIME> last_scale_time;
    extensions::field<int, HORIZONTAL_POD_AUTOSCALER_OBSERVED_GENERATION> observed_generation;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
