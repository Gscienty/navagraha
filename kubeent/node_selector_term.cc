#include "kubeent/node_selector_term.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char NODE_SELECTOR_TERM_MATCH_EXPRESSIONS[] = "matchExpressions";
char NODE_SELECTOR_TERM_MATCH_FIELDS[] = "matchFields";

void node_selector_term::serialize(node_selector_term & obj, std::ostringstream & str)
{
    extensions::link_serializer(extensions::link_serializer_type::object)
        .add(obj.match_expressions)
        .add(obj.match_fields)
        .serialize(str);
}

}
}
