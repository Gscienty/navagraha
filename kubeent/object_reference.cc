#include "kubeent/object_reference.hpp"

namespace navagraha {
namespace kubeent {

char OBJECT_REFERENCE_API_VERSION[] = "apiVersion";
char OBJECT_REFERENCE_FIELD_PATH[] = "fieldPath";
char OBJECT_REFERENCE_KIND[] = "kind";
char OBJECT_REFERENCE_NAME[] = "name";
char OBJECT_REFERENCE_NAMESPACE[] = "namespace";
char OBJECT_REFERENCE_RESOURCE_VERSION[] = "resourceVersion";
char OBJECT_REFERENCE_UID[] = "uid";

void object_reference::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->field_path)
        .add(this->kind)
        .add(this->name)
        .add(this->namespace_)
        .add(this->resource_version)
        .add(this->uid);
}

}
}
