#include "kubecil/node_selector_term.hpp"

namespace navagraha {
namespace kubecil {

char NODE_SELECTOR_TERM_MATCH_EXPRESSIONS[] = "matchExpressions";
char NODE_SELECTOR_TERM_MATCH_FIELDS[] = "matchFields";

void node_selector_term::serialize(node_selector_term & obj, std::ostringstream & str)
{
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> serializers = {
        extensions::field_serializer(obj.match_expressions),
        extensions::field_serializer(obj.match_fields)
    };

    str.put('{');
    extensions::fields_serialize(serializers, str);
    str.put('}');
}

}
}
