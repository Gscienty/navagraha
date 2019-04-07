#include "kubeent/secret_env_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char SECURITY_ENV_SOURCE_NAME[] = "name";
char SECURITY_ENV_SOURCE_OPTIONAL[] = "optional";

void secret_env_source::serialize(secret_env_source & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.name)
        .add(obj.optional)
        .serialize(str);
}

}
}
