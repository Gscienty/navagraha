#include "kubecli/label_selector_requirement.hpp"

namespace navagraha {
namespace kubectl {

char LABEL_SELECTOR_REQUIREMENT_KEY[] = "key";
char LABEL_SELECTOR_REQUIREMENT_OPERATOR[] = "operator";
char LABEL_SELECTOR_REQUIREMENT_VALUES[] = "values";

void label_selector_requirement::serialize(label_selector_requirement & obj,
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
