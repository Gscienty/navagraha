#ifndef _NAVAGRAHA_KUBEENT_ROLE_REF_H
#define _NAVAGRAHA_KUBEENT_ROLE_REF_H

#include "extensions/serializable.hpp"
#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ROLE_REF_API_GROUP[];
extern char ROLE_REF_KIND[];
extern char ROLE_REF_NAME[];

class role_ref : public extensions::serializable<role_ref> {
public:
    extensions::field<std::string, ROLE_REF_API_GROUP> api_group;
    extensions::field<std::string, ROLE_REF_KIND> kind;
    extensions::field<std::string, ROLE_REF_NAME> name;

    void bind(extensions::serializer_helper & helper);
};

}
}
#endif
