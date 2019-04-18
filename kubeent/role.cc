#include "kubeent/role.hpp"

namespace navagraha {
namespace kubeent {

char ROLE_API_VERSION[] = "apiVersion";
char ROLE_KIND[] = "kind";
char ROLE_METADATA[] = "metadata";
char ROLE_RULES[] = "rules";

void role::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->rules);
}

}
}
