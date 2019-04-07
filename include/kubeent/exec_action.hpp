#ifndef _NAVAGRAHA_KUBEENT_EXEC_ACTION_H
#define _NAVAGRAHA_KUBEENT_EXEC_ACTION_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char EXEC_ACTION_COMMAND[];

class exec_action {
public:
    extensions::field<
        extensions::special_list<std::string>,
        EXEC_ACTION_COMMAND> command;

    static void serialize(exec_action & obj, std::ostringstream & str);
};

}
}

#endif
