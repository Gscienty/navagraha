#include "kubeent/initializer.hpp"

namespace navagraha {
namespace kubeent {

char INITIALIZERS_NAME[] = "name";

void initializer::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name);
}

}
}
