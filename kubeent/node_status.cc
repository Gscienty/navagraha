#include "kubeent/node_status.hpp"

namespace navagraha {
namespace kubeent {

char NODE_STATUS_ADDRESSES[] = "addresses";
char NODE_STATUS_ALLOCATABLE[] = "allocatable";
char NODE_STATUS_CAPACITY[] = "capacity";
char NODE_STATUS_CONDITIONS[] = "conditions";
char NODE_STATUS_CONFIG[] = "config";
char NODE_STATUS_DAEMON_ENDPOINTS[] = "daemonEndpoints";
char NODE_STATUS_IMAGES[] = "images";
char NODE_STATUS_NODE_INFO[] = "nodeInfo";
char NODE_STATUS_PHASE[] = "phase";
char NODE_STATUS_VOLUMES_ATTACHED[] = "volumesAttached";
char NODE_STATUS_VOLUMES_IN_USE[] = "volumesInUse";

void node_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->addresses)
        .add(this->allocatable)
        .add(this->capacity)
        .add(this->conditions)
        .add(this->config)
        .add(this->daemon_endpoints)
        .add(this->images)
        .add(this->node_info)
        .add(this->phase)
        .add(this->volumes_attached)
        .add(this->volumes_in_use);
}

}
}
