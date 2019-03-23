#include "kubecil/label_selector.hpp"

namespace navagraha {
namespace kubecil {

char LABEL_SELECTOR_MATCH_EXPRESSIONS[] = "matchExpressions";
char LABEL_SELECTOR_MATCH_LABELS[] = "matchLabels";

void label_selector::serialize(label_selector & obj, std::ostringstream & str)
{
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> serializers = {
        extensions::field_serializer(obj.match_expressions),
        extensions::field_serializer(obj.match_labels)
    };

    str.put('{');
    extensions::fields_serialize(serializers, str);
    str.put('}');
}

}
}
