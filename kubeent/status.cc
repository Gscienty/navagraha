#include "kubeent/status.hpp"

namespace navagraha {
namespace kubeent {

char STATUS_API_VERSION[] = "apiVersion";
char STATUS_CODE[] = "code";
char STATUS_DETAILS[] = "details";
char STATUS_KIND[] = "kind";
char STATUS_MESSAGE[] = "message";
char STATUS_METADATA[] = "metadata";
char STATUS_REASON[] = "reason";
char STATUS_STATUS[] = "status";

void status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->code)
        .add(this->details)
        .add(this->kind)
        .add(this->message)
        .add(this->metadata)
        .add(this->reason)
        .add(this->status_);
}

}
}
