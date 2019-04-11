#include "kubeent/object_field_selector.hpp"

namespace navagraha {
namespace kubeent {

char OBJECT_FIELD_SELECTOR_API_VERSION[] = "apiVersion";
char OJBECT_FIELD_SELECTOR_FIELD_PATH[] = "fieldPath";

void object_field_selector::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->field_path);
}

}
}
