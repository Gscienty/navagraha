#include "kubeent/namespace_spec.hpp"

namespace navagraha {
namespace kubeent {

char NAMESPACE_SPEC_FINALIZERS[] = "finalizers";

void namespace_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->finalizers);
}

}
}
