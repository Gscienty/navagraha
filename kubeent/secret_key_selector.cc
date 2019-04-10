#include "kubeent/secret_key_selector.hpp"

namespace navagraha {
namespace kubeent {

char SECRET_KEY_SELECTOR_KEY[] = "key";
char SECRET_KEY_SELECTOR_NAME[] = "name";
char SECRET_KEY_SELECTOR_OPTIONAL[] = "optional";

void secret_key_selector::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->key)
        .add(this->name)
        .add(this->optional);
}

}
}
