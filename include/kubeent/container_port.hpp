#ifndef _NAVAGRAHA_KUBEENT_CONTAINER_PORT_H
#define _NAVAGRAHA_KUBEENT_CONTAINER_PORT_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CONTAINER_PORT_CONTAINER_PORT[];
extern char CONTAINER_PORT_HOST_IP[];
extern char CONTAINER_PORT_HOST_PORT[];
extern char CONTAINER_PORT_NAME[];
extern char CONTAINER_PORT_PROTOCOL[];

class container_port {
private:
    void bind(extensions::serializer_helper & helper);
public:
    extensions::field<int, CONTAINER_PORT_CONTAINER_PORT> container_port_;
    extensions::field<std::string, CONTAINER_PORT_HOST_IP> host_ip;
    extensions::field<int, CONTAINER_PORT_HOST_PORT> host_port;
    extensions::field<std::string, CONTAINER_PORT_NAME> name;
    extensions::field<std::string, CONTAINER_PORT_PROTOCOL> protocol;

    container_port & serialize(std::ostringstream & str);
    container_port & deserialize(std::istringstream & str);
    extensions::abstract_object to_abstract();
    static container_port to_special(extensions::abstract_object & obj);
};
}
}

#endif
