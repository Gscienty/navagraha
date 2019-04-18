#include "kubeent/secret.hpp"

namespace navagraha {
namespace kubeent {

char SECRET_API_VERSION[] = "apiVersion";
char SECRET_DATA[] = "data";
char SECRET_KIND[] = "kind";
char SECRET_METADATA[] = "metadata";
char SECRET_STRING_DATA[] = "stringData";
char SECRET_TYPE[] = "type";

void secret::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->data)
        .add(this->kind)
        .add(this->metadata)
        .add(this->string_data)
        .add(this->type);
}

}
}
