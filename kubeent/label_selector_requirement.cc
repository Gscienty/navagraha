#include "kubeent/label_selector_requirement.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char LABEL_SELECTOR_REQUIREMENT_KEY[] = "key";
char LABEL_SELECTOR_REQUIREMENT_OPERATOR[] = "operator";
char LABEL_SELECTOR_REQUIREMENT_VALUES[] = "values";

void label_selector_requirement::serialize(label_selector_requirement & obj,
                                           std::ostringstream & str)
{
    extensions::link_serializer(extensions::link_serializer_type::object)
        .add(obj.key)
        .add(obj.oper)
        .add(obj.values)
        .serialize(str);
}

}
}
