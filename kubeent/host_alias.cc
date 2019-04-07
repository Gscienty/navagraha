#include "kubeent/host_alias.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char HOST_ALIAS_HOSTNAMES[] = "hostnames";
char HOST_ALIAS_IP[] = "ip";

void host_alias::serialize(host_alias & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.hostnames)
        .add(obj.ip)
        .serialize(str);
}

}
}
