#include "kubeent/cluster_role.hpp"

namespace navagraha {
namespace kubeent {

char CLUSTER_ROLE_AGGREGATION_RULE[] = "aggregationRule";
char CLUSTER_ROLE_API_VERSION[] = "apiVersion";
char CLUSTER_ROLE_KIND[] = "kind";
char CLUSTER_ROLE_METADATA[] = "metadata";
char CLUSTER_ROLE_RULES[] = "rules";

void cluster_role::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->aggregation_rule_)
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->rules);
}

}
}
