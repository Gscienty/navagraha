#include "kubeent/stateful_set.hpp"

namespace navagraha {
namespace kubeent {

char STATEFUL_SET_API_VERSION[] = "apiVersion";
char STATEFUL_SET_KIND[] = "kind";
char STATEFUL_SET_METADATA[] = "metadata";
char STATEFUL_SET_SPEC[] = "spec";
char STATEFUL_SET_STATUS[] = "status";

void stateful_set::bind(extensions::serializer_helper & helper)
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
