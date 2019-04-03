#include "kubeent/key_to_path.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char KEY_TO_PATH_KEY[] = "key";
char KEY_TO_PATH_MODE[] = "mode";
char KEY_TO_PATH_PATH[] = "path";

void key_to_path::serialize(key_to_path & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.key)
        .add(obj.mode)
        .add(obj.path)
        .serialize(str);
}

}
}
