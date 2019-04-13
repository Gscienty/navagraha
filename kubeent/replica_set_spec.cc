#include "kubeent/replica_set_spec.hpp"

namespace navagraha {
namespace kubeent {

char REPLICA_SET_SPEC_MIN_READY_SECONDS[] = "minReadySeconds";
char REPLICA_SET_SPEC_REPLICAS[] = "replicas";
char REPLICA_SET_SPEC_SELECTOR[] = "selector";
char REPLICA_SET_SPEC_TEMPLATE[] = "template";

void replica_set_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->min_ready_seconds)
        .add(this->replicas)
        .add(this->selector)
        .add(this->template_);
}

}
}
