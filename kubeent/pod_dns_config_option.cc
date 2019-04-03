#include "kubeent/pod_dns_config_option.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char POD_DNS_CONFIG_OPTION_NAME[] = "name";
char POD_DNS_CONFIG_OPTION_VALUE[] = "value";

void pod_dns_config_option::serialize(pod_dns_config_option & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.name)
        .add(obj.value)
        .serialize(str);
}

}
}
