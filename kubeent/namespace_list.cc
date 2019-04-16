#include "kubeent/namespace_list.hpp"

namespace navagraha {
namespace kubeent {

char NAMESPACE_LIST_API_VERSION[] = "apiVersion";
char NAMESPACE_LIST_ITEMS[] = "items";
char NAMESPACE_LIST_KIND[] = "kind";
char NAMESPACE_LIST_METADATA[] = "metadata";

void namespace_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
