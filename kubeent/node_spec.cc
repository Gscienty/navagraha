#include "kubeent/node_spec.hpp"

namespace navagraha {
namespace kubeent {

char NODE_SPEC_CONFIG_SOURCE[] = "configSource";
char NODE_SPEC_EXTERNAL_ID[] = "externalID";
char NODE_SPEC_POD_CIDR[] = "podCIDR";
char NODE_SPEC_PROVIDER_ID[] = "providerID";
char NODE_SPEC_TAINTS[] = "taints";
char NODE_SPEC_UNSCHEDULABLE[] = "unschedulable";

void node_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->config_source)
        .add(this->external_id)
        .add(this->pod_cidr)
        .add(this->provider_id)
        .add(this->taints)
        .add(this->unschedulable);
}

}
}
