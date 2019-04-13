#include "kubeent/load_balancer_ingress.hpp"

namespace navagraha {
namespace kubeent {

char LOAD_BALANCER_INGRESS_HOSTNAME[] = "hostname";
char LOAD_BALANCER_INGRESS_IP[] = "ip";

void load_balancer_ingress::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->hostname)
        .add(this->ip);
}

}
}
