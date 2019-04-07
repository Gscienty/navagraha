#ifndef _NAVAGRAHA_KUBEENT_ENV_VAR_H
#define _NAVAGRAHA_KUBEENT_ENV_VAR_H

#include "extensions/field.hpp"
#include "kubeent/env_var_source.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ENV_VAR_NAME[];
extern char ENV_VAR_VALUE[];
extern char ENV_VAR_VALUE_FROM[];

class env_var {
public:
    extensions::field<std::string, ENV_VAR_NAME> name;
    extensions::field<std::string, ENV_VAR_VALUE> value;
    extensions::field<env_var_source, ENV_VAR_VALUE_FROM> value_from;

    static void serialize(env_var & obj, std::ostringstream & str);
};

}
}

#endif
