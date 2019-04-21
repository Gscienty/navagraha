#include "kubeent/endpoints_list.hpp"

namespace navagraha {
namespace kubeent {

char ENDPOINTS_LIST_API_VERSION[] = "apiVersion";
char ENDPOINTS_LIST_ITEMS[] = "items";
char ENDPOINTS_LIST_KIND[] = "kind";
char ENDPOINTS_LIST_METADATA[] = "metadata";

void endpoints_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
