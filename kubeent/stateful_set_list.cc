#include "kubeent/stateful_set_list.hpp"

namespace navagraha {
namespace kubeent {

char STATEFUL_SET_LIST_API_VERSION[] = "apiVersion";
char STATEFUL_SET_LIST_ITEMS[] = "items";
char STATEFUL_SET_LIST_KIND[] = "kind";
char STATEFUL_SET_LIST_METADATA[] = "metadata";


void stateful_set_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
