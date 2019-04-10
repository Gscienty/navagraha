#include "kubeent/empty_dir_volume_source.hpp"

namespace navagraha {
namespace kubeent {

char EMPTY_DIR_VOLUME_SOURCE_MEDIUM[] = "medium";
char EMPTY_DIR_VOLUME_SOURCE_SIZE_LIMIT[] = "sizeLimit";
void empty_dir_volume_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->medium)
        .add(this->size_limit);
}

}
}
