#include "kubeent/env_var_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char ENV_VAR_SOURCE_CONFIG_MAP_KEY_REF[] = "configMapKeyRef";
char ENV_VAR_SOURCE_FIELD_REF[] = "fieldRef";
char ENV_VAR_SOURCE_RESOURCE_FIELD_REF[] = "resourceFieldRef";
char ENV_VAR_SOURCE_SECRET_KEY_REF[] = "secretKeyRef";

void env_var_source::serialize(env_var_source & obj,
                               std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.config_map_key_ref)
        .add(obj.field_ref)
        .add(obj.resource_field_ref)
        .add(obj.secret_key_ref)
        .serialize(str);
}
}
}
