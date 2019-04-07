#ifndef _NAVAGRAHA_KUBEENT_POD_DNS_CONFIG_H
#define _NAVAGRAHA_KUBEENT_POD_DNS_CONFIG_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include "kubeent/pod_dns_config_option.hpp"

namespace navagraha {
namespace kubeent {

extern char POD_DNS_CONFIG_NAMESERVERS[];
extern char POD_DNS_CONFIG_OPTIONS[];
extern char POD_DNS_CONFIG_SEARCHES[];

class pod_dns_config {
public:
    extensions::field<
        extensions::special_list<std::string>,
        POD_DNS_CONFIG_NAMESERVERS> nameservers;
    extensions::field<
        extensions::special_list<pod_dns_config_option>,
        POD_DNS_CONFIG_OPTIONS> options;
    extensions::field<
        extensions::special_list<std::string>,
        POD_DNS_CONFIG_SEARCHES> searches;

    static void serialize(pod_dns_config & obj, std::ostringstream & str);
};

}
}

#endif
