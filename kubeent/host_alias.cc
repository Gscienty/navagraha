#include "kubeent/host_alias.hpp"

namespace navagraha {
namespace kubeent {

char HOST_ALIAS_HOSTNAMES[] = "hostnames";
char HOST_ALIAS_IP[] = "ip";

void host_alias::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->hostnames)
        .add(this->ip);
}

}
}
