#include "kubeent/node_selector_requirement.hpp"

namespace navagraha {
namespace kubeent {

char NODE_SELECTOR_REQUIREMENT_KEY[] = "key";
char NODE_SELECTOR_REQUIREMENT_OPERATOR[] = "operator";
char NODE_SELECTOR_REQUIREMENT_VALUES[] = "values";

void node_selector_requirement::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->key)
        .add(this->operator_)
        .add(this->values);
}

}
}
