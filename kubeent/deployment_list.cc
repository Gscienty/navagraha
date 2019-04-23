#include "kubeent/deployment_list.hpp"

namespace navagraha {
namespace kubeent {

char DEPLOYMENT_LIST_API_VERSION[] = "apiVersion";
char DEPLOYMENT_LIST_ITEMS[] = "items";
char DEPLOYMENT_LIST_KIND[] = "kind";
char DEPLOYMENT_LIST_METADATA[] = "metadata";

void deployment_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
