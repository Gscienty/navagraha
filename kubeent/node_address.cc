#include "kubeent/node_address.hpp"

namespace navagraha {
namespace kubeent {

char NODE_ADDRESS_ADDRESS[] = "address";
char NODE_ADDRESS_TYPE[] = "type";

void node_address::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->address)
        .add(this->type);
}

}
}
