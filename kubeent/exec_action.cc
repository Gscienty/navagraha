#include "kubeent/exec_action.hpp"

namespace navagraha {
namespace kubeent {

char EXEC_ACTION_COMMAND[] = "command";

void exec_action::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->command);
}

}
}

