#ifndef _NAVAGRAHA_KUBEENT_AGGREGATION_RULE_H
#define _NAVAGRAHA_KUBEENT_AGGREGATION_RULE_H

#include "extensions/serializable.hpp"
#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/label_selector.hpp"

namespace navagraha {
namespace kubeent {

extern char AGGREGATION_RULE_CLUSTER_ROLE_SELECTORS[];

class aggregation_rule : public extensions::serializable<aggregation_rule> {
public:
    extensions::field<
        extensions::special_list<label_selector>,
        AGGREGATION_RULE_CLUSTER_ROLE_SELECTORS> cluster_role_selectors;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
