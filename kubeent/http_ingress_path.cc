#include "kubeent/http_ingress_path.hpp"

namespace navagraha {
namespace kubeent {

char HTTP_INGRESS_PATH_BACKEND[] = "backend";
char HTTP_INGRESS_PATH_PATH[] = "path";

void http_ingress_path::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->backend)
        .add(this->path);
}

}
}
