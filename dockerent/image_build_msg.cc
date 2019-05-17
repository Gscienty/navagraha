#include "dockerent/image_build_msg.hpp"

namespace navagraha {
namespace dockerent {

char IMAGE_BUILD_MSG_STREAM[] = "stream";


void image_build_msg::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->stream);
}

}
}
