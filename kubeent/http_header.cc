#include "kubeent/http_header.hpp"

namespace navagraha {
namespace kubeent {

char HTTP_HEADER_NAME[] = "name";
char HTTP_HEADER_VALUE[] = "value";

void http_header::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->value);
}

}
}
