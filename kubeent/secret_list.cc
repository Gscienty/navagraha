#include "kubeent/secret_list.hpp"

namespace navagraha {
namespace kubeent {

char SECRET_LIST_API_VERSION[] = "apiVersion";
char SECRET_LIST_ITEMS[] = "items";
char SECRET_LIST_KIND[] = "kind";
char SECRET_LIST_METADATA[] = "metadata";

void secret_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
