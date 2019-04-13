#include "kubeent/ingress.hpp"

namespace navagraha {
namespace kubeent {

char INGRESS_API_VERSION[] = "apiVersion";
char INGRESS_KIND[] = "kind";
char INGRESS_METADATA[] = "metadata";
char INGRESS_SPEC[] = "spec";
char INGRESS_STATUS[] = "status";

void ingress::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->spec)
        .add(this->status);
}

}
}
