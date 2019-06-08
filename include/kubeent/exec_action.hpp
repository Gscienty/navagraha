#ifndef _NAVAGRAHA_KUBEENT_EXEC_ACTION_H
#define _NAVAGRAHA_KUBEENT_EXEC_ACTION_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char EXEC_ACTION_COMMAND[];

class exec_action : public extensions::serializable<exec_action> {
public:
    extensions::field<
        extensions::special_list<std::string>,
        EXEC_ACTION_COMMAND> command;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
