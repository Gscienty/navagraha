#include "kubeent/sysctl.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char SYSCTL_NAME[] = "name";
char SYSCTL_VALUE[] = "value";

void sysctl::serialize(sysctl & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.name)
        .add(obj.value)
        .serialize(str);
}

}
}
