#include "kubeent/node_selector.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char NODE_SELECTOR_NODE_SELECTOR_TERMS[] = "nodeSelectorTerms";

void node_selector::serialize(node_selector & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.node_selector_terms)
        .serialize(str);
}

}
}
