#include "kubeent/preconditions.hpp"

namespace navagraha {
namespace kubeent {

char PRECONDITIONS_UID[] = "uid";

void preconditions::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->uid);
}

}
}
