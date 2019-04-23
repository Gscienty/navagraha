#include "kubeent/daemon_set_list.hpp"

namespace navagraha {
namespace kubeent {

char DAEMON_SET_LIST_API_VERSION[] = "apiVersion";
char DAEMON_SET_LIST_ITEMS[] = "items";
char DAEMON_SET_LIST_KIND[] = "kind";
char DAEMON_SET_LIST_METADATA[] = "metadata";

void daemon_set_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
