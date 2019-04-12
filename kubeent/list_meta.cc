#include "kubeent/list_meta.hpp"

namespace navagraha {
namespace kubeent {

char LIST_META_CONTINUE[] = "continue";
char LIST_META_RESOURCE_VERSION[] = "resourceVersion";
char LIST_META_SELF_LINK[] = "selfLink";

void list_meta::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->continue_)
        .add(this->resource_version)
        .add(this->self_link);
}

}
}
