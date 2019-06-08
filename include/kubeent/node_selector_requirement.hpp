#ifndef _NAVAGRAHA_KUBEENT_NODE_SELECTOR_REQUIREMENT_H
#define _NAVAGRAHA_KUBEENT_NODE_SELECTOR_REQUIREMENT_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char NODE_SELECTOR_REQUIREMENT_KEY[];
extern char NODE_SELECTOR_REQUIREMENT_OPERATOR[];
extern char NODE_SELECTOR_REQUIREMENT_VALUES[];

class node_selector_requirement : public extensions::serializable<node_selector_requirement> {
public:
    extensions::field<
        std::string,
        NODE_SELECTOR_REQUIREMENT_KEY> key;
    extensions::field<
        std::string,
        NODE_SELECTOR_REQUIREMENT_OPERATOR> operator_;
    extensions::field<
        extensions::special_list<std::string>,
        NODE_SELECTOR_REQUIREMENT_VALUES> values;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
