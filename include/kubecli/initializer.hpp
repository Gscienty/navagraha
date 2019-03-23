#ifndef _NAVAGRAHA_EXTENSION_INITIALIZER_H
#define _NAVAGRAHA_EXTENSION_INITIALIZER_H

#include "extensions/field.hpp"
#include <string>
#include <sstream>

namespace navagraha {
namespace kubectl {

extern char INITIALIZERS_NAME[];

class initializer {
public:
    extensions::field<std::string, INITIALIZERS_NAME> name;

    static void serialize(initializer & obj, std::ostringstream & str);
};

}
}

#endif
