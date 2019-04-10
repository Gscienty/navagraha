#include "kubeent/key_to_path.hpp"

namespace navagraha {
namespace kubeent {

char KEY_TO_PATH_KEY[] = "key";
char KEY_TO_PATH_MODE[] = "mode";
char KEY_TO_PATH_PATH[] = "path";

void key_to_path::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->key)
        .add(this->mode)
        .add(this->path);
}

}
}
