#include "kubeent/env_var.hpp"

namespace navagraha {
namespace kubeent {

char ENV_VAR_NAME[] = "name";
char ENV_VAR_VALUE[] = "value";
char ENV_VAR_VALUE_FROM[] = "valueFrom";

void env_var::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->value)
        .add(this->value_from);
}

}
}
