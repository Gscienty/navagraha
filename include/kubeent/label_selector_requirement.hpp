#ifndef _NAVAGRAHA_KUBEENT_LABEL_SELECTOR_REQUIREMENT_H
#define _NAVAGRAHA_KUBEENT_LABEL_SELECTOR_REQUIREMENT_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>
#include <sstream>

namespace navagraha {
namespace kubeent {

extern char LABEL_SELECTOR_REQUIREMENT_KEY[];
extern char LABEL_SELECTOR_REQUIREMENT_OPERATOR[];
extern char LABEL_SELECTOR_REQUIREMENT_VALUES[];

class label_selector_requirement : public serializable<label_selector_requirement> {
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

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
