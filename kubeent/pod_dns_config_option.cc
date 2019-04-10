#include "kubeent/pod_dns_config_option.hpp"

namespace navagraha {
namespace kubeent {

char POD_DNS_CONFIG_OPTION_NAME[] = "name";
char POD_DNS_CONFIG_OPTION_VALUE[] = "value";

void pod_dns_config_option::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->value);
}

}
}
