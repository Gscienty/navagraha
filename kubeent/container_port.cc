#include "kubeent/container_port.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_PORT_CONTAINER_PORT[] = "containerPort";
char CONTAINER_PORT_HOST_IP[] = "hostIP";
char CONTAINER_PORT_HOST_PORT[] = "hostPort";
char CONTAINER_PORT_NAME[] = "name";
char CONTAINER_PORT_PROTOCOL[] = "protocol";

extensions::link_serializer container_port::bind(container_port & obj)
{
    return extensions::link_serializer()
        .add(obj.container_port_)
        .add(obj.host_ip)
        .add(obj.host_port)
        .add(obj.name)
        .add(obj.protocol);
}

void container_port::serialize(container_port & obj, std::ostringstream & str)
{
    container_port::bind(obj).serialize(str);
}

void container_port::deserialize(container_port & obj, std::istringstream & str)
{
    container_port::bind(obj).deserialize(str);
}

}
}
