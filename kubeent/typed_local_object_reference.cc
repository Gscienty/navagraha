#include "kubeent/typed_local_object_reference.hpp"

namespace navagraha {
namespace kubeent {

char TYPED_LOCAL_OBJECT_REFERENCE_API_GROUP[] = "apiGroup";
char TYPED_LOCAL_OBJECT_REFERENCE_KIND[] = "kind";
char TYPED_LOCAL_OBJECT_REFERENCE_NAME[] = "name";

void typed_local_object_reference::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_group)
        .add(this->kind)
        .add(this->name);
}

}
}
