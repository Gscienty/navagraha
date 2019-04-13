#include "kubeent/ingress_tls.hpp"

namespace navagraha {
namespace kubeent {

char INGRESS_TLS_HOSTS[] = "hosts";
char INGRESS_TLS_SECRET_NAME[] = "secretName";

void ingress_tls::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->hosts)
        .add(this->secret_name);
}

}
}
