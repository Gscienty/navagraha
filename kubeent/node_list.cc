#include "kubeent/node_list.hpp"

namespace navagraha {
namespace kubeent {

char NODE_LIST_API_VERSION[] = "apiVersion";
char NODE_LIST_ITEMS[] = "items";
char NODE_LIST_KIND[] = "kind";
char NODE_LIST_METADATA[] = "metadata";

void node_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
