#include "kubeent/initializers.hpp"

namespace navagraha {
namespace kubeent {

char INITIALIZERS_PENDING[] = "pending";

void initializers::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->pending);
}

}
}
