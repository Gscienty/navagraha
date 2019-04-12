#include "kubeent/pod_status.hpp"

namespace navagraha {
namespace kubeent {

char POD_STATUS_CONDITIONS[] = "conditions";
char POD_STATUS_CONTAINER_STATUSES[] = "containerStatuses";
char POD_STATUS_HOST_IP[] = "hostIP";
char POD_STATUS_INIT_CONTAINER_STATUSES[] = "initContainerStatuses";
char POD_STATUS_MESSAGE[] = "message";
char POD_STATUS_NOMINATED_NODE_NAME[] = "nominatedNodeName";
char POD_STATUS_PHASE[] = "phase";
char POD_STATUS_POD_IP[] = "podIP";
char POD_STATUS_QOS_CLASS[] = "qosClass";
char POD_STATUS_REASON[] = "reason";
char POD_STATUS_START_TIME[] = "startTime";

void pod_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->conditions)
        .add(this->container_statuses)
        .add(this->host_ip)
        .add(this->init_container_statuses)
        .add(this->message)
        .add(this->nominated_node_name)
        .add(this->phase)
        .add(this->pod_ip)
        .add(this->qos_class)
        .add(this->reason)
        .add(this->start_time);
}

}
}
