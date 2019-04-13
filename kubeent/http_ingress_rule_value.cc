#include "kubeent/http_ingress_rule_value.hpp"

namespace navagraha {
namespace kubeent {

char HTTP_INGRESS_RULE_VALUE_PATHS[] = "paths";

void http_ingress_rule_value::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->paths);
}

}
}
