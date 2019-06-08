#ifndef _NAVAGRAHA_KUBEENT_ENV_VAR_H
#define _NAVAGRAHA_KUBEENT_ENV_VAR_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/env_var_source.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ENV_VAR_NAME[];
extern char ENV_VAR_VALUE[];
extern char ENV_VAR_VALUE_FROM[];

class env_var : public extensions::serializable<env_var> {
public:
    extensions::field<std::string, ENV_VAR_NAME> name;
    extensions::field<std::string, ENV_VAR_VALUE> value;
    extensions::field<env_var_source, ENV_VAR_VALUE_FROM> value_from;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
