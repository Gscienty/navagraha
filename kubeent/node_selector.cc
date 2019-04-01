#include "kubeent/node_selector.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

void node_selector::serialize(node_selector & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.node_selector_terms)
        .serialize(str);
}

}
}
