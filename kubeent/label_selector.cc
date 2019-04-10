#include "kubeent/label_selector.hpp"

namespace navagraha {
namespace kubeent {

char LABEL_SELECTOR_MATCH_EXPRESSIONS[] = "matchExpressions";
char LABEL_SELECTOR_MATCH_LABELS[] = "matchLabels";

void label_selector::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->match_expressions)
        .add(this->match_labels);
}


}
}
