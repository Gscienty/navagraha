#ifndef _NAVAGRAHA_KUBECLI_NODE_SELECTOR_TERM_H
#define _NAVAGRAHA_KUBECLI_NODE_SELECTOR_TERM_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include "kubecil/node_selector_requirement.hpp"

namespace navagraha {
namespace kubecil {

extern char NODE_SELECTOR_TERM_MATCH_EXPRESSIONS[];
extern char NODE_SELECTOR_TERM_MATCH_FIELDS[];

class node_selector_term {
public:
    extensions::field<
        extensions::special_list<node_selector_requirement>,
        NODE_SELECTOR_TERM_MATCH_EXPRESSIONS> match_expressions;
    extensions::field<
        extensions::special_list<node_selector_requirement>,
        NODE_SELECTOR_TERM_MATCH_FIELDS> match_fields;

    static void serialize(node_selector_term & obj, std::ostringstream & str);

};

}
}

#endif
