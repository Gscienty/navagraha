#include "kubeent/env_from_source.hpp"

namespace navagraha {
namespace kubeent {

char ENV_FROM_SOURCE_CONFIG_MAP_REF[] = "configMapRef";
char ENV_FROM_SOURCE_PREFIX[] = "prefix";
char ENV_FROM_SOURCE_SECRET_REF[] = "secretRef";

void env_from_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->config_map_ref)
        .add(this->prefix)
        .add(this->secret_ref);
}

}
}
