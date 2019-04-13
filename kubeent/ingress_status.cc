#include "kubeent/ingress_status.hpp"

namespace navagraha {
namespace kubeent {

char INGRESS_STATUS_LOAD_BALANCER[] = "loadBalancer";

void ingress_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->load_balancer);
}

}
}
