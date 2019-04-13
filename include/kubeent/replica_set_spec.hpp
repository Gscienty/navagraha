#ifndef _NAVAGRAHA_KUBEENT_REPLICA_SET_SPEC_H
#define _NAVAGRAHA_KUBEENT_REPLICA_SET_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/label_selector.hpp"
#include "kubeent/pod_template_spec.hpp"

namespace navagraha {
namespace kubeent {

extern char REPLICA_SET_SPEC_MIN_READY_SECONDS[];
extern char REPLICA_SET_SPEC_REPLICAS[];
extern char REPLICA_SET_SPEC_SELECTOR[];
extern char REPLICA_SET_SPEC_TEMPLATE[];

class replica_set_spec : public serializable<replica_set_spec> {
public:
    extensions::field<int, REPLICA_SET_SPEC_MIN_READY_SECONDS> min_ready_seconds;
    extensions::field<int, REPLICA_SET_SPEC_REPLICAS> replicas;
    extensions::field<label_selector, REPLICA_SET_SPEC_SELECTOR> selector;
    extensions::field<pod_template_spec, REPLICA_SET_SPEC_TEMPLATE> template_;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
