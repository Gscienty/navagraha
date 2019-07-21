#include "kubeent/cross_version_object_reference.hpp"

namespace navagraha {
namespace kubeent {

char CROSS_VERSION_OBJECT_REFERENCE_API_VERSION[] = "apiVersion";
char CROSS_VERSION_OBJECT_REFERENCE_KIND[] = "kind";
char CROSS_VERSION_OBJECT_REFERENCE_NAME[] = "name";

void cross_version_object_reference::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->name);
}

}
}
