#include "kubeent/node_selector_requirement.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char NODE_SELECTOR_REQUIREMENT_KEY[] = "key";
char NODE_SELECTOR_REQUIREMENT_OPERATOR[] = "operator";
char NODE_SELECTOR_REQUIREMENT_VALUES[] = "values";

void node_selector_requirement::serialize(node_selector_requirement & obj,
                                          std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.key)
        .add(obj.oper)
        .add(obj.values)
        .serialize(str);
}

}
}
