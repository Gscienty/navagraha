#include "kubeent/resource_field_selector.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char RESOURCE_FIELD_SELECTOR_CONTAINER_NAME[] = "containerName";
char RESOURCE_FIELD_SELECTOR_DIVISOR[] = "divisor";
char RESOURCE_FIELD_SELECTOR_RESOURCE[] = "resource";

void resource_field_selector::serialize(resource_field_selector & obj,
                                        std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.container_name)
        .add(obj.divisor)
        .add(obj.resource)
        .serialize(str);
}

}
}
