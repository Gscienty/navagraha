#ifndef _NAVAGRAHA_KUBEENT_SERVICE_PORT_H
#define _NAVAGRAHA_KUBEENT_SERVICE_PORT_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SERVICE_PORT_NAME[];
extern char SERVICE_PORT_NODE_PORT[];
extern char SERVICE_PORT_PORT[];
extern char SERVICE_PORT_PROTOCOL[];
extern char SERVICE_PORT_TARGET_PORT[];

class service_port : public serializable<service_port> {
public:
    extensions::field<std::string, SERVICE_PORT_NAME> name;
    extensions::field<int, SERVICE_PORT_NODE_PORT> node_port;
    extensions::field<int, SERVICE_PORT_PORT> port;
    extensions::field<std::string, SERVICE_PORT_PROTOCOL> protocol;
    extensions::field<int, SERVICE_PORT_TARGET_PORT> target_port;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
