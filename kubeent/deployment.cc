#include "kubeent/deployment.hpp"

namespace navagraha {
namespace kubeent {

char DEPLOYMENT_API_VERSION[] = "apiVersion";
char DEPLOYMENT_KIND[] = "kind";
char DEPLOYMENT_METADATA[] = "metadata";
char DEPLOYMENT_SPEC[] = "spec";
char DEPLOYMENT_STATUS[] = "status";

void deployment::bind(extensions::serializer_helper & helper)
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
