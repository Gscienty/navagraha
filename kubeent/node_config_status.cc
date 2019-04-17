#include "kubeent/node_config_status.hpp"

namespace navagraha {
namespace kubeent {

char NODE_CONFIG_STATUS_ACTIVE[] = "active";
char NODE_CONFIG_STATUS_ASSIGNED[] = "assigned";
char NODE_CONFIG_STATUS_ERROR[] = "error";
char NODE_CONFIG_STATUS_LAST_KNOWN_GOOD[] = "lastKnownGood";

void node_config_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->active)
        .add(this->assigned)
        .add(this->error)
        .add(this->last_known_good);
}

}
}
