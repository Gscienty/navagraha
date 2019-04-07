#include "kubeent/http_header.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char HTTP_HEADER_NAME[] = "name";
char HTTP_HEADER_VALUE[] = "value";

void serialize(http_header & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.name)
        .add(obj.value)
        .serialize(str);
}

}
}
