#include "kubeent/local_object_reference.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char LOCAL_OBJECT_REFERENCE_NAME[] = "name";

void local_object_reference::serialize(local_object_reference & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.name)
        .serialize(str);
}

}
}
