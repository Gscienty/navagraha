#ifndef _NAVAGRAHA_KUBEENT_ENDPOINT_ADDRESS_H
#define _NAVAGRAHA_KUBEENT_ENDPOINT_ADDRESS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_reference.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ENDPOINT_ADDRESS_HOSTNAME[];
extern char ENDPOINT_ADDRESS_IP[];
extern char ENDPOINT_ADDRESS_NODE_NAME[];
extern char ENDPOINT_ADDRESS_TARGET_REF[];

class endpoint_address : public extensions::serializable<endpoint_address> {
public:
    extensions::field<std::string, ENDPOINT_ADDRESS_HOSTNAME> hostname;
    extensions::field<std::string, ENDPOINT_ADDRESS_IP> ip;
    extensions::field<std::string, ENDPOINT_ADDRESS_NODE_NAME> node_name;
    extensions::field<object_reference, ENDPOINT_ADDRESS_TARGET_REF> target_ref;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
