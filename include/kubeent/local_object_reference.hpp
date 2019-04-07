#ifndef _NAVAGRAHA_KUBEENT_LOCAL_OBJECT_REFERENCE_H
#define _NAVAGRAHA_KUBEENT_LOCAL_OBJECT_REFERENCE_H

#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char LOCAL_OBJECT_REFERENCE_NAME[];

class local_object_reference {
public:
    extensions::field<std::string, LOCAL_OBJECT_REFERENCE_NAME> name;

    static void serialize(local_object_reference & obj, std::ostringstream & str);
};

}
}

#endif
