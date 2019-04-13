#ifndef _NAVAGRAHA_KUBEENT_REPLICATION_CONTROLLER_SPEC_H
#define _NAVAGRAHA_KUBEENT_REPLICATION_CONTROLLER_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/common_object.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/pod_template_spec.hpp"

namespace navagraha {
namespace kubeent {

extern char REPLICATION_CONTROLLER_SPEC_MIN_READY_SECONDS[];
extern char REPLICATION_CONTROLLER_SPEC_REPLICAS[];
extern char REPLICATION_CONTROLLER_SPEC_SELECTOR[];
extern char REPLCIATION_CONTROLLER_SPEC_TEMPLATE[];

class replication_controller_spec : public serializable<replication_controller_spec> {
public:
    extensions::field<int, REPLICATION_CONTROLLER_SPEC_MIN_READY_SECONDS> min_ready_seconds;
    extensions::field<int, REPLICATION_CONTROLLER_SPEC_REPLICAS> replicas;
    extensions::field<extensions::common_object, REPLICATION_CONTROLLER_SPEC_SELECTOR> selector;
    extensions::field<pod_template_spec, REPLCIATION_CONTROLLER_SPEC_TEMPLATE> template_;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
