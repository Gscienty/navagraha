#include "kubeent/pod_dns_config.hpp"

namespace navagraha {
namespace kubeent {

char POD_DNS_CONFIG_NAMESERVERS[] = "nameservers";
char POD_DNS_CONFIG_OPTIONS[] = "options";
char POD_DNS_CONFIG_SEARCHES[] = "searches";

void pod_dns_config::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->nameservers)
        .add(this->options)
        .add(this->searches);
}

}
}
