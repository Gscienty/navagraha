#include "kubeent/node.hpp"

namespace navagraha {
namespace kubeent {

char NODE_API_VERSION[] = "apiVersion";
char NODE_KIND[] = "kind";
char NODE_METADATA[] = "metadata";
char NODE_SPEC[] = "spec";
char NODE_STATUS[] = "status";

void node::bind(extensions::serializer_helper & helper)
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
