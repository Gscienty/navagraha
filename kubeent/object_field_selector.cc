#include "kubeent/object_field_selector.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char OBJECT_FIELD_SELECTOR_API_VERSION[] = "apiVersion";
char OJBECT_FIELD_SELECTOR_FIELD_PATH[] = "fieldPath";

void object_field_selector::serialize(object_field_selector & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.api_version)
        .add(obj.field_path)
        .serialize(str);
}

}
}
