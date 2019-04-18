#ifndef _NAVAGRAHA_KUBEENT_ROLE_H
#define _NAVAGRAHA_KUBEENT_ROLE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/policy_rule.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ROLE_API_VERSION[];
extern char ROLE_KIND[];
extern char ROLE_METADATA[];
extern char ROLE_RULES[];

class role : public serializable<role> {
public:
    extensions::field<std::string, ROLE_API_VERSION> api_version;
    extensions::field<std::string, ROLE_KIND> kind;
    extensions::field<object_meta, ROLE_METADATA> metadata;
    extensions::field<extensions::special_list<policy_rule>, ROLE_RULES> rules;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
