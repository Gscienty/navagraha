#include "kubeent/service_list.hpp"

namespace navagraha {
namespace kubeent {

char SERVICE_LIST_API_VERSION[] = "apiVersion";
char SERVICE_LIST_ITEMS[] = "items";
char SERVICE_LIST_KIND[] = "kind";
char SERVICE_LIST_METADATA[] = "metadata";

void service_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
