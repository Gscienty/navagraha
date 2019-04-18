#ifndef _NAVAGRAHA_KUBEENT_POLICY_RULE_H
#define _NAVAGRAHA_KUBEENT_POLICY_RULE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POLICY_RULE_API_GROUPS[];
extern char POLICY_RULE_NON_RESOURCE_URLS[];
extern char POLICY_RULE_RESOURCE_NAMES[];
extern char POLICY_RULE_RESOURCES[];
extern char POLICY_RULE_VERBS[];

class policy_rule : public serializable<policy_rule> {
public:
    extensions::field<extensions::special_list<std::string>,
        POLICY_RULE_API_GROUPS> api_groups;
    extensions::field<extensions::special_list<std::string>,
        POLICY_RULE_NON_RESOURCE_URLS> non_resource_urls;
    extensions::field<extensions::special_list<std::string>,
        POLICY_RULE_RESOURCE_NAMES> resource_names;
    extensions::field<extensions::special_list<std::string>,
        POLICY_RULE_RESOURCES> resources;
    extensions::field<extensions::special_list<std::string>,
        POLICY_RULE_VERBS> verbs;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
