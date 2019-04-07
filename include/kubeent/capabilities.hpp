#ifndef _NAVAGRAHA_KUBEENT_CAPABILITIES_H
#define _NAVAGRAHA_KUBEENT_CAPABILITIES_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CAPABILITIES_ADD[];
extern char CAPABILITIES_DROP[];

class capabilities {
public:
    extensions::field<
        extensions::special_list<std::string>,
        CAPABILITIES_ADD> add;
    extensions::field<
        extensions::special_list<std::string>,
        CAPABILITIES_DROP> drop;

    static void serialize(capabilities & obj, std::ostringstream & str);
};
}
}

#endif
