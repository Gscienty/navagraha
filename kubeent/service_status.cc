#include "kubeent/service_status.hpp"

namespace navagraha {
namespace kubeent {

char SERVICE_STATUS_LOAD_BALANCER[] = "loadBalancer";

void service_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->load_balancer);
}

}
}
