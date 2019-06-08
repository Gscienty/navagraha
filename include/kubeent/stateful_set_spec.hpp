#ifndef _NAVAGRAHA_KUBEENT_STATEFUL_SET_SPEC_H
#define _NAVAGRAHA_KUBEENT_STATEFUL_SET_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/label_selector.hpp"
#include "kubeent/pod_template_spec.hpp"
#include "kubeent/stateful_set_update_strategy.hpp"
#include "kubeent/persistent_volume_claim.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char STATEFUL_SET_SPEC_POD_MANAGEMENT_POLICY[];
extern char STATEFUL_SET_SPEC_REPLICAS[];
extern char STATEFUL_SET_SPEC_REVISION_HISTORY_LIMIT[];
extern char STATEFUL_SET_SPEC_SELECTOR[];
extern char STATEFUL_SET_SPEC_SERVICE_NAME[];
extern char STATEFUL_SET_SPEC_TEMPLATE[];
extern char STATEFUL_SET_SPEC_UPDATE_STRATEGY[];
extern char STATEFUL_SET_SPEC_VOLUME_CLAIM_TEMPLATES[];

class stateful_set_spec : public extensions::serializable<stateful_set_spec> {
public:
    extensions::field<std::string, STATEFUL_SET_SPEC_POD_MANAGEMENT_POLICY> pod_management_policy;
    extensions::field<int, STATEFUL_SET_SPEC_REPLICAS> replicas;
    extensions::field<int, STATEFUL_SET_SPEC_REVISION_HISTORY_LIMIT> revision_history_limit;
    extensions::field<label_selector, STATEFUL_SET_SPEC_SELECTOR> selector;
    extensions::field<std::string, STATEFUL_SET_SPEC_SERVICE_NAME> service_name;
    extensions::field<pod_template_spec, STATEFUL_SET_SPEC_TEMPLATE> template_;
    extensions::field<stateful_set_update_strategy, STATEFUL_SET_SPEC_UPDATE_STRATEGY> update_strategy;
    extensions::field<
        extensions::special_list<persistent_volume_claim>,
        STATEFUL_SET_SPEC_VOLUME_CLAIM_TEMPLATES> volume_claim_templates;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
