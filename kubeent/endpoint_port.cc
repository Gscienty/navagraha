#include "kubeent/endpoint_port.hpp"

namespace navagraha {
namespace kubeent {

char ENDPOINT_PORT_NAME[] = "name";
char ENDPOINT_PORT_PORT[] = "port";
char ENDPOINT_PORT_PROTOCOL[] = "protocol";

void endpoint_port::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->port)
        .add(this->protocol);
}

}
}
