#include "kubeent/capabilities.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char CAPABILITIES_ADD[] = "add";
char CAPABILITIES_DROP[] = "drop";

void capabilities::serialize(capabilities & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.add)
        .add(obj.drop)
        .serialize(str);
}
}
}
