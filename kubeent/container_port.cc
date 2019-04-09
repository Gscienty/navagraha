#include "kubeent/container_port.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_PORT_CONTAINER_PORT[] = "containerPort";
char CONTAINER_PORT_HOST_IP[] = "hostIP";
char CONTAINER_PORT_HOST_PORT[] = "hostPort";
char CONTAINER_PORT_NAME[] = "name";
char CONTAINER_PORT_PROTOCOL[] = "protocol";

extensions::serializer_helper container_port::bind(extensions::link_serializer_type type)
{
    return extensions::serializer_helper(type)
        .add(this->container_port_)
        .add(this->host_ip)
        .add(this->host_port)
        .add(this->name)
        .add(this->protocol);
}

container_port & container_port::serialize(std::ostringstream & str)
{
    container_port::bind(extensions::link_serializer_type_serialize).serialize(str);
    return *this;
}

container_port & container_port::deserialize(std::istringstream & str)
{
    container_port::bind(extensions::link_serializer_type_deserialize).deserialize(str);
    return *this;
}

extensions::abstract_object container_port::to_abstract()
{
    return container_port::bind(extensions::link_serializer_type_to_abstract).to_abstract();
}

container_port container_port::to_special(extensions::abstract_object & obj)
{
    container_port ret;

    return ret;
}

}
}
