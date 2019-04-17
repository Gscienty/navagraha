#include "kubeent/container_image.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_IMAGE_NAMES[] = "names";
char CONTAINER_IMAGE_SIZE_BYTES[] = "sizeBytes";

void container_image::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->names)
        .add(this->size_bytes);
}

}
}
