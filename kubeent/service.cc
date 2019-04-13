#include "kubeent/service.hpp"

namespace navagraha {
namespace kubeent {

char SERVICE_API_VERSION[] = "apiVersion";
char SERVICE_KIND[] = "kind";
char SERVICE_METADATA[] = "metadata";
char SERVICE_SPEC[] = "spec";
char SERVICE_STATUS[] = "status";

void service::bind(extensions::serializer_helper & helper)
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
