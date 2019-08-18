#include "kubeent/horizontal_pod_autoscaler_list.hpp"

namespace navagraha {
namespace kubeent {

char HORIZONTAL_POD_AUTOSCALER_LIST_API_VERSION[] = "apiVersion";
char HORIZONTAL_POD_AUTOSCALER_LIST_ITEMS[] = "items";
char HORIZONTAL_POD_AUTOSCALER_LIST_KIND[] = "kind";
char HORIZONTAL_POD_AUTOSCALER_LIST_METADATA[] = "metadata";

void horizontal_pod_autoscaler_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
