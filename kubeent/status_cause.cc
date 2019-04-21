#include "kubeent/status_cause.hpp"

namespace navagraha {
namespace kubeent {

char STATUS_CAUSE_FIELD[] = "field";
char STATUS_CAUSE_MESSAGE[] = "message";
char STATUS_CAUSE_REASON[] = "reason";

void status_cause::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->field)
        .add(this->message)
        .add(this->reason);
}

}
}
