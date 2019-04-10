#ifndef _NAVAGRAHA_KUBEENT_INITIALIZER_H
#define _NAVAGRAHA_KUBEENT_INITIALIZER_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>
#include <sstream>

namespace navagraha {
namespace kubeent {

extern char INITIALIZERS_NAME[];

class initializer : public serializable<initializer> {
public:
    extensions::field<std::string, INITIALIZERS_NAME> name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
