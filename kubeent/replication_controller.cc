#include "kubeent/replication_controller.hpp"

namespace navagraha {
namespace kubeent {

char REPLICATION_CONTROLLER_API_VERSION[] = "apiVersion";
char REPLICATION_CONTROLLER_KIND[] = "kind";
char REPLICATION_CONTROLLER_METADATA[] = "metadata";
char REPLCIATION_CONTROLLER_SPEC[] = "spec";
char REPLCIATION_CONTROLLER_STATUS[] = "status";

void replication_controller::bind(extensions::serializer_helper & helper)
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
