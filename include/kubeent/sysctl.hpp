#ifndef _NAVAGRAHA_KUBEENT_SYSCTL_H
#define _NAVAGRAHA_KUBEENT_SYSCTL_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SYSCTL_NAME[];
extern char SYSCTL_VALUE[];

class sysctl : public serializable<sysctl> {
public:
    extensions::field<std::string, SYSCTL_NAME> name;
    extensions::field<std::string, SYSCTL_VALUE> value;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
