#include "kubeent/daemon_set_spec.hpp"

namespace navagraha {
namespace kubeent {

char DAEMON_SET_SPEC_MIN_READY_SECONDS[] = "minReadySeconds";
char DAEMON_SET_SPEC_REVISION_HISTORY_LIMIT[] = "revisionHistoryLimit";
char DAEMON_SET_SPEC_SELECTOR[] = "selector";
char DAEMON_SET_SPEC_TEMPLATE[] = "template";
char DAEMON_SET_SPEC_UPDATE_STRATEGY[] = "updateStrategy";

void daemon_set_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->min_ready_seconds)
        .add(this->revision_history_limit)
        .add(this->selector)
        .add(this->template_)
        .add(this->update_strategy);
}

}
}
