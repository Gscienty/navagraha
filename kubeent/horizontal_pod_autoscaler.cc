#include "kubeent/horizontal_pod_autoscaler.hpp"

namespace navagraha {
namespace kubeent {

char HORIZONTAL_POD_AUTOSCALER_API_VRESION[] = "apiVersion";
char HORIZONTAL_POD_AUTOSCALER_KIND[] = "kind";
char HORIZONTAL_POD_AUTOSCALER_METADATA[] = "metadata";
char HORIZONTAL_POD_AUTOSCALER_SPEC[] = "spec";
char HORIZONTAL_POD_AUTOSCALER_STATUS[] = "status";

void horizontal_pod_autoscaler::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->spec)
        .add(this->status);
}

}
}
