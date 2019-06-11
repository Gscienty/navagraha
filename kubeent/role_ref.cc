#include "kubeent/role_ref.hpp"

namespace navagraha {
namespace kubeent {

char ROLE_REF_API_GROUP[] = "apiGroup";
char ROLE_REF_KIND[] = "kind";
char ROLE_REF_NAME[] = "name";

void role_ref::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_group)
        .add(this->kind)
        .add(this->name);
}

}
}
