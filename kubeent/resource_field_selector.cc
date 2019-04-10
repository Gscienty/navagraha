#include "kubeent/resource_field_selector.hpp"

namespace navagraha {
namespace kubeent {

char RESOURCE_FIELD_SELECTOR_CONTAINER_NAME[] = "containerName";
char RESOURCE_FIELD_SELECTOR_DIVISOR[] = "divisor";
char RESOURCE_FIELD_SELECTOR_RESOURCE[] = "resource";

void resource_field_selector::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->container_name)
        .add(this->divisor)
        .add(this->resource);
}

}
}
