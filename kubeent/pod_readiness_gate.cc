#include "kubeent/pod_readiness_gate.hpp"

namespace navagraha {
namespace kubeent {

char POD_READINESS_GATE_CONDITION_TYPE[] = "conditionType";

void pod_readiness_gate::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->condition_type);
}

}
}
