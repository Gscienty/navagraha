#ifndef _NAVAGRAHA_KUBEENT_POD_READINESS_GATE_H
#define _NAVAGRAHA_KUBEENT_POD_READINESS_GATE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POD_READINESS_GATE_CONDITION_TYPE[];

class pod_readiness_gate : public extensions::serializable<pod_readiness_gate> {
public:
    extensions::field<std::string, POD_READINESS_GATE_CONDITION_TYPE> condition_type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
