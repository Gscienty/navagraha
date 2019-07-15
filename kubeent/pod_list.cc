#include "kubeent/pod_list.hpp"

namespace navagraha {
namespace kubeent {

char POD_LIST_API_VERSION[] = "apiVersion";
char POD_LIST_KIND[] = "kind";
char POD_LIST_ITEMS[] = "items";
char POD_LIST_METADATA[] = "metadata";


void pod_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->items)
        .add(this->metadata);
}

}
}
