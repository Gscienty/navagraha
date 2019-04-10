#include "kubeent/container_port.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_PORT_CONTAINER_PORT[] = "containerPort";
char CONTAINER_PORT_HOST_IP[] = "hostIP";
char CONTAINER_PORT_HOST_PORT[] = "hostPort";
char CONTAINER_PORT_NAME[] = "name";
char CONTAINER_PORT_PROTOCOL[] = "protocol";

void container_port::bind(extensions::serializer_helper & helper)
{
    helper.add(this->container_port_)
        .add(this->host_ip)
        .add(this->host_port)
        .add(this->name)
        .add(this->protocol);
}

}
}
