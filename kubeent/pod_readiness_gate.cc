#include "kubeent/pod_readiness_gate.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char POD_READINESS_GATE_NAME[] = "name";

void pod_readiness_gate::serialize(pod_readiness_gate & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.condition_type)
        .serialize(str);
}
}
}
