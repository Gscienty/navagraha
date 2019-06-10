#ifndef _NAVAGRAHA_KUBEENT_CLUSTER_ROLE_H
#define _NAVAGRAHA_KUBEENT_CLUSTER_ROLE_H

#include "extensions/serializable.hpp"
#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/aggregation_rule.hpp"
#include "kubeent/policy_rule.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CLUSTER_ROLE_AGGREGATION_RULE[];
extern char CLUSTER_ROLE_API_VERSION[];
extern char CLUSTER_ROLE_KIND[];
extern char CLUSTER_ROLE_METADATA[];
extern char CLUSTER_ROLE_RULES[];

class cluster_role : public extensions::serializable<cluster_role> {
public:
    extensions::field<aggregation_rule, CLUSTER_ROLE_AGGREGATION_RULE> aggregation_rule_;
    extensions::field<std::string, CLUSTER_ROLE_API_VERSION> api_version;
    extensions::field<std::string, CLUSTER_ROLE_KIND> kind;
    extensions::field<object_meta, CLUSTER_ROLE_METADATA> metadata;
    extensions::field<extensions::special_list<policy_rule>, CLUSTER_ROLE_RULES> rules;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
