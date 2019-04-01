#include "kubeent/secret_key_selector.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char SECRET_KEY_SELECTOR_KEY[] = "key";
char SECRET_KEY_SELECTOR_NAME[] = "name";
char SECRET_KEY_SELECTOR_OPTIONAL[] = "optional";

void secret_key_selector::serialize(secret_key_selector & obj,
                                    std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.key)
        .add(obj.name)
        .add(obj.optional)
        .serialize(str);
}
}
}
