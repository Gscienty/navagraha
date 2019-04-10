#include "kubeent/secret_env_source.hpp"

namespace navagraha {
namespace kubeent {

char SECURITY_ENV_SOURCE_NAME[] = "name";
char SECURITY_ENV_SOURCE_OPTIONAL[] = "optional";

void secret_env_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->optional);
}

}
}
