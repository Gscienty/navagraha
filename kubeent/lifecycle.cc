#include "kubeent/lifecycle.hpp"

namespace navagraha {
namespace kubeent {

char LIFECYCLE_POST_START[] = "postStart";
char LIFECYCLE_PRE_STOP[] = "preStop";

void lifecycle::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->post_start)
        .add(this->pre_stop);
}

}
}
