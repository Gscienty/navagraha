#include "kubeent/replica_set.hpp"

namespace navagraha {
namespace kubeent {

char REPLICA_SET_API_VERSION[] = "apiVersion";
char REPLICA_SET_KIND[] = "kind";
char REPLICA_SET_METADATA[] = "metadata";
char REPLCIA_SET_SPEC[] = "spec";
char REPLCIA_SET_STATUS[] = "status";

void replica_set::bind(extensions::serializer_helper & helper)
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
