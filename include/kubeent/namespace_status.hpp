#ifndef _NAVAGRAHA_KUBEENT_NAMESPACE_STATUS_H
#define _NAVAGRAHA_KUBEENT_NAMESPACE_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NAMESPACE_STATUS_PHASE[];

class namespace_status : public extensions::serializable<namespace_status> {
public:
    extensions::field<std::string, NAMESPACE_STATUS_PHASE> phase;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
