#ifndef _NAVAGRAHA_KUBEENT_NODE_SELECTOR_TERM_H
#define _NAVAGRAHA_KUBEENT_NODE_SELECTOR_TERM_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/node_selector_requirement.hpp"

namespace navagraha {
namespace kubeent {

extern char NODE_SELECTOR_TERM_MATCH_EXPRESSIONS[];
extern char NODE_SELECTOR_TERM_MATCH_FIELDS[];

class node_selector_term : public extensions::serializable<node_selector_term> {
public:
    extensions::field<
        extensions::special_list<node_selector_requirement>,
        NODE_SELECTOR_TERM_MATCH_EXPRESSIONS> match_expressions;
    extensions::field<
        extensions::special_list<node_selector_requirement>,
        NODE_SELECTOR_TERM_MATCH_FIELDS> match_fields;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
