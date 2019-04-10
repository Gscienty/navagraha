#include "kubeent/capabilities.hpp"

namespace navagraha {
namespace kubeent {

char CAPABILITIES_ADD[] = "add";
char CAPABILITIES_DROP[] = "drop";

void capabilities::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->add)
        .add(this->drop);
}

}
}
