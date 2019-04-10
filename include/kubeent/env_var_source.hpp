#ifndef _NAVAGRAHA_KUBEENT_ENV_VAR_SOURCE_H
#define _NAVAGRAHA_KUBEENT_ENV_VAR_SOURCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/config_map_key_selector.hpp"
#include "kubeent/object_field_selector.hpp"
#include "kubeent/resource_field_selector.hpp"
#include "kubeent/secret_key_selector.hpp"

namespace navagraha {
namespace kubeent {

extern char ENV_VAR_SOURCE_CONFIG_MAP_KEY_REF[];
extern char ENV_VAR_SOURCE_FIELD_REF[];
extern char ENV_VAR_SOURCE_RESOURCE_FIELD_REF[];
extern char ENV_VAR_SOURCE_SECRET_KEY_REF[];

class env_var_source : public serializable<env_var_source> {
public:
    extensions::field<
        config_map_key_selector,
        ENV_VAR_SOURCE_CONFIG_MAP_KEY_REF> config_map_key_ref;
    extensions::field<
        object_field_selector,
        ENV_VAR_SOURCE_FIELD_REF> field_ref;
    extensions::field<
        resource_field_selector,
        ENV_VAR_SOURCE_RESOURCE_FIELD_REF> resource_field_ref;
    extensions::field<
        secret_key_selector,
        ENV_VAR_SOURCE_SECRET_KEY_REF> secret_key_ref;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
