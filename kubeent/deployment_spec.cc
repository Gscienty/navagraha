#include "kubeent/deployment_spec.hpp"

namespace navagraha {
namespace kubeent {

char DEPLOYMENT_SPEC_MIN_READY_SECONDS[] = "minReadySeconds";
char DEPLOYMENT_SPCE_PAUSED[] = "paused";
char DEPLOYMENT_SPEC_PROGRESS_DEADLINE_SECONDS[] = "progressDeadlineSeconds";
char DEPLOYMENT_SPEC_REPLICAS[] = "replicas";
char DEPLOYMENT_SPEC_REVISION_HISTORY_LIMIT[] = "revisionHistoryLimit";
char DEPOLYMENT_SPEC_SELECTOR[] = "selector";
char DEPLOYMENT_SPEC_STRATEGY[] = "strategy";
char DEPLOYMENT_SPEC_TEMPLATE[] = "template";

void deployment_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->min_ready_seconds)
        .add(this->paused)
        .add(this->progress_deadline_seconds)
        .add(this->replicas)
        .add(this->revision_history_limit)
        .add(this->selector)
        .add(this->strategy)
        .add(this->template_);
}

}
}
