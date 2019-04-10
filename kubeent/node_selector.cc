#include "kubeent/node_selector.hpp"

namespace navagraha {
namespace kubeent {

char NODE_SELECTOR_NODE_SELECTOR_TERMS[] = "nodeSelectorTerms";

void node_selector::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->node_selector_terms);
}

}
}
