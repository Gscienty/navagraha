#include "kubeent/env_var_source.hpp"

namespace navagraha {
namespace kubeent {

char ENV_VAR_SOURCE_CONFIG_MAP_KEY_REF[] = "configMapKeyRef";
char ENV_VAR_SOURCE_FIELD_REF[] = "fieldRef";
char ENV_VAR_SOURCE_RESOURCE_FIELD_REF[] = "resourceFieldRef";
char ENV_VAR_SOURCE_SECRET_KEY_REF[] = "secretKeyRef";

void env_var_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->config_map_key_ref)
        .add(this->field_ref)
        .add(this->resource_field_ref)
        .add(this->secret_key_ref);
}
}
}
