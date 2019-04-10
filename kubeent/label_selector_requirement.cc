#include "kubeent/label_selector_requirement.hpp"

namespace navagraha {
namespace kubeent {

char LABEL_SELECTOR_REQUIREMENT_KEY[] = "key";
char LABEL_SELECTOR_REQUIREMENT_OPERATOR[] = "operator";
char LABEL_SELECTOR_REQUIREMENT_VALUES[] = "values";

void label_selector_requirement::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->key)
        .add(this->oper)
        .add(this->values);
}

}
}
