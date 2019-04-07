#include "kubeent/env_from_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char ENV_FROM_SOURCE_CONFIG_MAP_REF[] = "configMapRef";
char ENV_FROM_SOURCE_PREFIX[] = "prefix";
char ENV_FROM_SOURCE_SECRET_REF[] = "secretRef";

void env_from_source::serialize(env_from_source & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.config_map_ref)
        .add(obj.prefix)
        .add(obj.secret_ref)
        .add(str);
}
}
}
