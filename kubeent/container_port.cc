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

container_port & container_port::serialize(std::ostringstream & str)
{
    extensions::serializer_helper()
        .serialize(&container_port::bind, this, str);
    return *this;
}

container_port & container_port::deserialize(std::istringstream & str)
{
    extensions::serializer_helper()
        .deserialize(&container_port::bind, this, str);
    return *this;
}

extensions::abstract_object container_port::to_abstract()
{
    return extensions::serializer_helper()
        .to_abstract(&container_port::bind, this);
}

container_port container_port::to_special(extensions::abstract_object & obj)
{
    return extensions::serializer_helper()
        .to_special(&container_port::bind, container_port(), obj);
}

}
}
