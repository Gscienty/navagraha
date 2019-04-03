#include "kubeent/deployment_spec.hpp"
#include "extensions/link_serializer.hpp"

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


void deployment_spec::serialize(deployment_spec & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.min_ready_seconds)
        .add(obj.paused)
        .add(obj.progress_deadline_seconds)
        .add(obj.replicas)
        .add(obj.revision_history_limit)
        .add(obj.selector)
        .add(obj.strategy)
        .add(obj.template_)
        .serialize(str);
}

}
}
