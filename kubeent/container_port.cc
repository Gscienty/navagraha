#include "kubeent/container_port.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_PORT_CONTAINER_PORT[] = "containerPort";
char CONTAINER_PORT_HOST_IP[] = "hostIP";
char CONTAINER_PORT_HOST_PORT[] = "hostPort";
char CONTAINER_PORT_NAME[] = "name";
char CONTAINER_PORT_PROTOCOL[] = "protocol";

extensions::link_serializer container_port::bind(container_port & obj, extensions::link_serializer_type type)
{
    return extensions::link_serializer(type)
        .add(obj.container_port_)
        .add(obj.host_ip)
        .add(obj.host_port)
        .add(obj.name)
        .add(obj.protocol);
}

void container_port::serialize(container_port & obj, std::ostringstream & str)
{
    container_port::bind(obj, extensions::link_serializer_type_serialize).serialize(str);
}

void container_port::deserialize(container_port & obj, std::istringstream & str)
{
    container_port::bind(obj, extensions::link_serializer_type_deserialize).deserialize(str);
}

extensions::absobj_field_value container_port::to_abstract(container_port & obj)
{
    return container_port::bind(obj, extensions::link_serializer_type_to_abstract).to_abstract();
}

container_port & container_port::serialize(std::ostringstream & str)
{
    container_port::serialize(*this, str);
    return *this;
}

container_port & container_port::deserialize(std::istringstream & str)
{
    container_port::deserialize(*this, str);
    return *this;
}

extensions::absobj_field_value container_port::to_abstract()
{
    return  container_port::to_abstract(*this);
}

}
}
