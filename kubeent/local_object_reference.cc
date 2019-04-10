#include "kubeent/local_object_reference.hpp"

namespace navagraha {
namespace kubeent {

char LOCAL_OBJECT_REFERENCE_NAME[] = "name";

void local_object_reference::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name);
}

}
}
