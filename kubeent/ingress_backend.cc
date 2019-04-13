#include "kubeent/ingress_backend.hpp"

namespace navagraha {
namespace kubeent {

char INGRESS_BACKEND_SERVICE_NAME[] = "serviceName";
char INGRESS_BACKEDN_SERVICE_PORT[] = "servicePort";

void ingress_backend::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->service_name)
        .add(this->service_port);
}

}
}
