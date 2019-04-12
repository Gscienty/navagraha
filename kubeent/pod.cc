#include "kubeent/pod.hpp"

namespace navagraha {
namespace kubeent {

char POD_API_VERSION[] = "apiVersion";
char POD_KIND[] = "kind";
char POD_METADATA[] = "metadata";
char POD_SPEC[] = "spec";
char POD_STATUS[] = "status";

void pod::bind(extensions::serializer_helper & helper)
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
