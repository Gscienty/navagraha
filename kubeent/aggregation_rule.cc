#include "kubeent/aggregation_rule.hpp"

namespace navagraha {
namespace kubeent {

char AGGREGATION_RULE_CLUSTER_ROLE_SELECTORS[] = "clusterRoleSelectors";

void aggregation_rule::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->cluster_role_selectors);
}

}
}
