#include "kubeent/namespace_status.hpp"

namespace navagraha {
namespace kubeent {

char NAMESPACE_STATUS_PHASE[] = "phase";

void namespace_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->phase);
}

}
}
