#ifndef _NAVAGRAHA_KUBEENT_HORIZONTAL_POD_AUTOSCALER_H
#define _NAVAGRAHA_KUBEENT_HORIZONTAL_POD_AUTOSCALER_H

#include "extensions/field.hpp"
#include "extensions/serializable.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/horizontal_pod_autoscaler_spec.hpp"
#include "kubeent/horizontal_pod_autoscaler_status.hpp"
#include "kubeent/object_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char HORIZONTAL_POD_AUTOSCALER_API_VRESION[];
extern char HORIZONTAL_POD_AUTOSCALER_KIND[];
extern char HORIZONTAL_POD_AUTOSCALER_METADATA[];
extern char HORIZONTAL_POD_AUTOSCALER_SPEC[];
extern char HORIZONTAL_POD_AUTOSCALER_STATUS[];

class horizontal_pod_autoscaler : public extensions::serializable<horizontal_pod_autoscaler> {
public:
    extensions::field<std::string, HORIZONTAL_POD_AUTOSCALER_API_VRESION> api_version;
    extensions::field<std::string, HORIZONTAL_POD_AUTOSCALER_KIND> kind;
    extensions::field<object_meta, HORIZONTAL_POD_AUTOSCALER_METADATA> metadata;
    extensions::field<horizontal_pod_autoscaler_spec, HORIZONTAL_POD_AUTOSCALER_SPEC> spec;
    extensions::field<horizontal_pod_autoscaler_status, HORIZONTAL_POD_AUTOSCALER_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
