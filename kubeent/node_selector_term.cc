#include "kubeent/node_selector_term.hpp"

namespace navagraha {
namespace kubeent {

char NODE_SELECTOR_TERM_MATCH_EXPRESSIONS[] = "matchExpressions";
char NODE_SELECTOR_TERM_MATCH_FIELDS[] = "matchFields";

void node_selector_term::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->match_expressions)
        .add(this->match_fields);
}

}
}
