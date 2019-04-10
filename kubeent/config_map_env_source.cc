#include "kubeent/config_map_env_source.hpp"

namespace navagraha {
namespace kubeent {

char CONFIG_MAP_ENV_SOURCE_NAME[] = "name";
char CONFIG_MAP_ENV_SOURCE_OPTIONAL[] = "optional";

void config_map_env_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->optional);
}
}
}
