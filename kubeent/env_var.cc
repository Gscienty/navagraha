#include "kubeent/env_var.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char ENV_VAR_NAME[] = "name";
char ENV_VAR_VALUE[] = "value";
char ENV_VAR_VALUE_FROM[] = "valueFrom";

void env_var::serialize(env_var & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.name)
        .add(obj.value)
        .add(obj.value_from)
        .serialize(str);
}

}
}
