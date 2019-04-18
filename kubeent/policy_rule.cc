#include "kubeent/policy_rule.hpp"

namespace navagraha {
namespace kubeent {

char POLICY_RULE_API_GROUPS[] = "apiGroups";
char POLICY_RULE_NON_RESOURCE_URLS[] = "nonResourceURLs";
char POLICY_RULE_RESOURCE_NAMES[] = "resourceNames";
char POLICY_RULE_RESOURCES[] = "resources";
char POLICY_RULE_VERBS[] = "verbs";

void policy_rule::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_groups)
        .add(this->non_resource_urls)
        .add(this->resource_names)
        .add(this->resources)
        .add(this->verbs);
}

}
}
