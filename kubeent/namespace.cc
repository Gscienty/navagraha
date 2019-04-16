#include "kubeent/namespace.hpp"

namespace navagraha {
namespace kubeent {

char NAMESPACE_API_VERSION[] = "apiVersion";
char NAMESPACE_KIND[] = "kind";
char NAMESPACE_METADATA[] = "metadata";
char NAMESPACE_SPEC[] = "spec";
char NAMESPACE_STATUS[] = "status";

void namespace_::bind(extensions::serializer_helper & helper)
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
