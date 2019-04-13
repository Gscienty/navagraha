#include "kubeent/load_balancer_status.hpp"

namespace navagraha {
namespace kubeent {

char LOAD_BALANCER_STATUS_INGRESS[] = "ingress";

void load_balancer_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->ingress);
}

}
}
