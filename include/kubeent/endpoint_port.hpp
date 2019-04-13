#ifndef _NAVAGRAHA_KUBEENT_ENDPOINT_PORT_H
#define _NAVAGRAHA_KUBEENT_ENDPOINT_PORT_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ENDPOINT_PORT_NAME[];
extern char ENDPOINT_PORT_PORT[];
extern char ENDPOINT_PORT_PROTOCOL[];

class endpoint_port : public serializable<endpoint_port> {
public:
    extensions::field<std::string, ENDPOINT_PORT_NAME> name;
    extensions::field<int, ENDPOINT_PORT_PORT> port;
    extensions::field<std::string, ENDPOINT_PORT_PROTOCOL> protocol;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
