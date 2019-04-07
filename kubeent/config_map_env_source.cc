#include "kubeent/config_map_env_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char CONFIG_MAP_ENV_SOURCE_NAME[] = "name";
char CONFIG_MAP_ENV_SOURCE_OPTIONAL[] = "optional";

void config_map_env_source::serialize(config_map_env_source & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.name)
        .add(obj.optional)
        .serialize(str);
}

}
}
