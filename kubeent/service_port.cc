#include "kubeent/service_port.hpp"

namespace navagraha {
namespace kubeent {

char SERVICE_PORT_NAME[] = "name";
char SERVICE_PORT_NODE_PORT[] = "nodePort";
char SERVICE_PORT_PORT[] = "port";
char SERVICE_PORT_PROTOCOL[] = "protocol";
char SERVICE_PORT_TARGET_PORT[] = "targetPort";

void service_port::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->node_port)
        .add(this->port)
        .add(this->protocol)
        .add(this->target_port);
}

}
}
