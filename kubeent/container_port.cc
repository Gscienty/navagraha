#include "kubeent/container_port.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_PORT_CONTAINER_PORT[] = "containerPort";
char CONTAINER_PORT_HOST_IP[] = "hostIP";
char CONTAINER_PORT_HOST_PORT[] = "hostPort";
char CONTAINER_PORT_NAME[] = "name";
char CONTAINER_PORT_PROTOCOL[] = "protocol";

void container_port::serialize(container_port & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.container_port_)
        .add(obj.host_ip)
        .add(obj.host_port)
        .add(obj.protocol)
        .serialize(str);
}
}
}
