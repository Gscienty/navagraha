#ifndef _NAVAGRAHA_KUBEENT_NODE_SELECTOR_REQUIREMENT_H
#define _NAVAGRAHA_KUBEENT_NODE_SELECTOR_REQUIREMENT_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include <sstream>

namespace navagraha {
namespace kubeent {

extern char NODE_SELECTOR_REQUIREMENT_KEY[];
extern char NODE_SELECTOR_REQUIREMENT_OPERATOR[];
extern char NODE_SELECTOR_REQUIREMENT_VALUES[];

class node_selector_requirement {
public:
    extensions::field<
        std::string,
        NODE_SELECTOR_REQUIREMENT_KEY> key;
    extensions::field<
        std::string,
        NODE_SELECTOR_REQUIREMENT_OPERATOR> oper;
    extensions::field<
        extensions::special_list<std::string>,
        NODE_SELECTOR_REQUIREMENT_VALUES> values;

    static void serialize(node_selector_requirement & obj, std::ostringstream & str);
};

}
}

#endif
