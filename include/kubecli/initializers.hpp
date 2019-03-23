#ifndef _NAVAGRAHA_KUBECTL_INITIALIZERS_H
#define _NAVAGRAHA_KUBECTL_INITIALIZERS_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include <sstream>

namespace navagraha {
namespace kubectl {

extern char INITIALIZERS_PENDING[];

class initializers {
public:
    extensions::field<extensions::list_wrapper, INITIALIZERS_PENDING> pending;

    static void serialize(initializers & obj, std::ostringstream & str);
};

}
}

#endif
