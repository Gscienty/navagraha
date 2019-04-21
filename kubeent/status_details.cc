#include "kubeent/status_details.hpp"

namespace navagraha {
namespace kubeent {

char STATUS_DETAILS_CAUSES[] = "causes";
char STATUS_DETAILS_GROUP[] = "group";
char STATUS_DETAILS_KIND[] = "kind";
char STATUS_DETAILS_NAME[] = "name";
char STATUS_DETAILS_RETRY_AFTER_SECONDS[] = "retryAfterSeconds";
char STATUS_DETAILS_UID[] = "uid";

void status_details::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->causes)
        .add(this->group)
        .add(this->kind)
        .add(this->name)
        .add(this->retry_after_seconds)
        .add(this->uid);
}

}
}
