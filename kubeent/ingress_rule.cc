#include "kubeent/ingress_rule.hpp"

namespace navagraha {
namespace kubeent {

char INGRESS_RULE_HOST[] = "host";
char INGRESS_RULE_HTTP[] = "http";

void ingress_rule::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->host)
        .add(this->http);
}

}
}
