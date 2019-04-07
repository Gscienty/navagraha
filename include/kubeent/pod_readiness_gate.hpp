#ifndef _NAVAGRAHA_KUBEENT_POD_READINESS_GATE_H
#define _NAVAGRAHA_KUBEENT_POD_READINESS_GATE_H

#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POD_READINESS_GATE_CONDITION_TYPE[];

class pod_readiness_gate {
public:
    extensions::field<std::string, POD_READINESS_GATE_CONDITION_TYPE> condition_type;

    static void serialize(pod_readiness_gate & obj, std::ostringstream & str);
};

}
}

#endif
