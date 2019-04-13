#include "kubeent/endpoint_address.hpp"

namespace navagraha {
namespace kubeent {

char ENDPOINT_ADDRESS_HOSTNAME[] = "hostname";
char ENDPOINT_ADDRESS_IP[] = "ip";
char ENDPOINT_ADDRESS_NODE_NAME[] = "nodeName";
char ENDPOINT_ADDRESS_TARGET_REF[] = "targetRef";

void endpoint_address::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->hostname)
        .add(this->ip)
        .add(this->node_name)
        .add(this->target_ref);
}

}
}
