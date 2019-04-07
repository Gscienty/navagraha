#ifndef _NAVAGRAHA_KUBEENT_ENV_FROM_SOURCE_H
#define _NAVAGRAHA_KUBEENT_ENV_FROM_SOURCE_H

#include "extensions/field.hpp"
#include "kubeent/config_map_env_source.hpp"
#include "kubeent/secret_env_source.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ENV_FROM_SOURCE_CONFIG_MAP_REF[];
extern char ENV_FROM_SOURCE_PREFIX[];
extern char ENV_FROM_SOURCE_SECRET_REF[];

class env_from_source {
public:
    extensions::field<
        config_map_env_source,
        ENV_FROM_SOURCE_CONFIG_MAP_REF> config_map_ref;
    extensions::field<
        std::string,
        ENV_FROM_SOURCE_PREFIX> prefix;
    extensions::field<
        secret_env_source,
        ENV_FROM_SOURCE_SECRET_REF> secret_ref;

    static void serialize(env_from_source & obj, std::ostringstream & str);
};
}
}

#endif
