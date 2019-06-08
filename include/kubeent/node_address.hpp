#ifndef _NAVAGRAHA_KUBEENT_NODE_ADDRESS_H
#define _NAVAGRAHA_KUBEENT_NODE_ADDRESS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NODE_ADDRESS_ADDRESS[];
extern char NODE_ADDRESS_TYPE[];

class node_address : public extensions::serializable<node_address> {
public:
    extensions::field<std::string, NODE_ADDRESS_ADDRESS> address;
    extensions::field<std::string, NODE_ADDRESS_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
