#ifndef _NAVAGRAHA_KUBEENT_HORIZONTAL_POD_AUTOSCALER_SPEC_H
#define _NAVAGRAHA_KUBEENT_HORIZONTAL_POD_AUTOSCALER_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializable.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/cross_version_object_reference.hpp"

namespace navagraha {
namespace kubeent {

extern char HORIZONTAL_POD_AUTOSCALER_SPEC_MAX_REPLICAS[];
extern char HORIZONTAL_POD_AUTOSCALER_SPEC_MIN_REPLICAS[];
extern char HORIZONTAL_POD_AUTOSCALER_SPEC_SCALE_TARGET_REF[];
extern char HORIZONTAL_POD_AUTOSCALER_SPEC_TARGET_CPU_UTILIZATION_PERCENTAGE[];

class horizontal_pod_autoscaler_spec : public extensions::serializable<horizontal_pod_autoscaler_spec> {
public:
    extensions::field<int, HORIZONTAL_POD_AUTOSCALER_SPEC_MIN_REPLICAS> min_replicas;
    extensions::field<int, HORIZONTAL_POD_AUTOSCALER_SPEC_MAX_REPLICAS> max_replicas;
    extensions::field<cross_version_object_reference, HORIZONTAL_POD_AUTOSCALER_SPEC_SCALE_TARGET_REF> scale_target_ref;
    extensions::field<int, HORIZONTAL_POD_AUTOSCALER_SPEC_TARGET_CPU_UTILIZATION_PERCENTAGE> cpu_utilization_percentage;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
