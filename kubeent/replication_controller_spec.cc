#include "kubeent/replication_controller_spec.hpp"

namespace navagraha {
namespace kubeent {

char REPLICATION_CONTROLLER_SPEC_MIN_READY_SECONDS[] = "minReadySeconds";
char REPLICATION_CONTROLLER_SPEC_REPLICAS[] = "replicas";
char REPLICATION_CONTROLLER_SPEC_SELECTOR[] = "selector";
char REPLCIATION_CONTROLLER_SPEC_TEMPLATE[] = "template";

void replication_controller_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->min_ready_seconds)
        .add(this->replicas)
        .add(this->selector)
        .add(this->template_);
}

}
}
