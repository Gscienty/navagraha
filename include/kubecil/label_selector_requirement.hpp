#ifndef _NAVAGRAHA_KUBECTL_LABEL_SELECTOR_REQUIREMENT_H
#define _NAVAGRAHA_KUBECTL_LABEL_SELECTOR_REQUIREMENT_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include <string>
#include <sstream>

namespace navagraha {
namespace kubecil {

extern char LABEL_SELECTOR_REQUIREMENT_KEY[];
extern char LABEL_SELECTOR_REQUIREMENT_OPERATOR[];
extern char LABEL_SELECTOR_REQUIREMENT_VALUES[];

class label_selector_requirement {
public:
    extensions::field<
        std::string,
        LABEL_SELECTOR_REQUIREMENT_KEY> key;
    extensions::field<
        std::string,
        LABEL_SELECTOR_REQUIREMENT_OPERATOR> oper;
    extensions::field<
        extensions::special_list<std::string>,
        LABEL_SELECTOR_REQUIREMENT_VALUES> values;

    static void serialize(label_selector_requirement & obj, std::ostringstream & str);
};

}
}

#endif
