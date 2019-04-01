#include "kubeent/label_selector.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char LABEL_SELECTOR_MATCH_EXPRESSIONS[] = "matchExpressions";
char LABEL_SELECTOR_MATCH_LABELS[] = "matchLabels";

void label_selector::serialize(label_selector & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.match_expressions)
        .add(obj.match_labels)
        .serialize(str);
}

}
}
