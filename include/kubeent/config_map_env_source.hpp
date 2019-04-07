#ifndef _NAVAGRAHA_KUBEENT_CONFIG_MAP_ENV_SOURCE_H
#define _NAVAGRAHA_KUBEENT_CONFIG_MAP_ENV_SOURCE_H

#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CONFIG_MAP_ENV_SOURCE_NAME[];
extern char CONFIG_MAP_ENV_SOURCE_OPTIONAL[];

class config_map_env_source {
public:
    extensions::field<std::string, CONFIG_MAP_ENV_SOURCE_NAME> name;
    extensions::field<bool, CONFIG_MAP_ENV_SOURCE_OPTIONAL> optional;

    static void serialize(config_map_env_source & obj, std::ostringstream & str);
};

}
}

#endif
