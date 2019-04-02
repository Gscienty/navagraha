#include "kubeent/exec_action.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char EXEC_ACTION_COMMAND[] = "command";

void exec_action::serialize(exec_action & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.command)
        .serialize(str);
}

}
}

