#ifndef _NAVAGRAHA_KUBEENT_INITIALIZER_H
#define _NAVAGRAHA_KUBEENT_INITIALIZER_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char INITIALIZERS_NAME[];

class initializer : public extensions::serializable<initializer> {
public:
    extensions::field<std::string, INITIALIZERS_NAME> name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
