#ifndef _NAVAGRAHA_KUBEENT_SYSCTL_H
#define _NAVAGRAHA_KUBEENT_SYSCTL_H

#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SYSCTL_NAME[];
extern char SYSCTL_VALUE[];

class sysctl {
public:
    extensions::field<std::string, SYSCTL_NAME> name;
    extensions::field<std::string, SYSCTL_VALUE> value;

    static void serialize(sysctl & obj, std::ostringstream & str);
};

}
}

#endif
