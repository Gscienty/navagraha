#include "kubecil/node_selector_requirement.hpp"

namespace navagraha {
namespace kubecil {

char NODE_SELECTOR_REQUIREMENT_KEY[] = "key";
char NODE_SELECTOR_REQUIREMENT_OPERATOR[] = "operator";
char NODE_SELECTOR_REQUIREMENT_VALUES[] = "values";

void node_selector_requirement::serialize(node_selector_requirement & obj,
                                          std::ostringstream & str)
{
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> serializers = {
        extensions::field_serializer(obj.key),
        extensions::field_serializer(obj.oper),
        extensions::field_serializer(obj.values)
    };

    str.put('{');
    extensions::fields_serialize(serializers, str);
    str.put('}');
}

}
}
