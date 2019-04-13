#include "kubeent/ingress_spec.hpp"

namespace navagraha {
namespace kubeent {

char INGRESS_SPEC_BACKEND[] = "backend";
char INGRESS_SPEC_RULES[] = "rules";
char INGRESS_SPEC_TLS[] = "tls";

void ingress_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->backend)
        .add(this->rules)
        .add(this->tls);
}

}
}
