#include "kubeent/daemon_set.hpp"

namespace navagraha {
namespace kubeent {

char DAEMON_SET_API_VERSION[] = "apiVersion";
char DAEMON_SET_KIND[] = "kind";
char DAEMON_SET_METADATA[] = "metadata";
char DAEMON_SET_SPEC[] = "spec";
char DAEMON_SET_STATUS[] = "status";

void daemon_set::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->spec)
        .add(this->status);
}

}
}
