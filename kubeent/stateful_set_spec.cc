#include "kubeent/stateful_set_spec.hpp"

namespace navagraha {
namespace kubeent {

char STATEFUL_SET_SPEC_POD_MANAGEMENT_POLICY[] = "podManagementPolicy";
char STATEFUL_SET_SPEC_REPLICAS[] = "replicas";
char STATEFUL_SET_SPEC_REVISION_HISTORY_LIMIT[] = "revisionHistoryLimit";
char STATEFUL_SET_SPEC_SELECTOR[] = "selector";
char STATEFUL_SET_SPEC_SERVICE_NAME[] = "serviceName";
char STATEFUL_SET_SPEC_TEMPLATE[] = "template";
char STATEFUL_SET_SPEC_UPDATE_STRATEGY[] = "updateStrategy";
char STATEFUL_SET_SPEC_VOLUME_CLAIM_TEMPLATES[] = "volumeClaimTemplates";

void stateful_set_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->pod_management_policy)
        .add(this->replicas)
        .add(this->revision_history_limit)
        .add(this->selector)
        .add(this->service_name)
        .add(this->template_)
        .add(this->update_strategy)
        .add(this->volume_claim_templates);
}

}
}
