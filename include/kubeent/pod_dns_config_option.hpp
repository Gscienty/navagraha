#ifndef _NAVAGRAHA_KUBEENT_POD_DNS_CONFIG_OPTION_H
#define _NAVAGRAHA_KUBEENT_POD_DNS_CONFIG_OPTION_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POD_DNS_CONFIG_OPTION_NAME[];
extern char POD_DNS_CONFIG_OPTION_VALUE[];

class pod_dns_config_option : public serializable<pod_dns_config_option> {
public:
    extensions::field<std::string, POD_DNS_CONFIG_OPTION_NAME> name;
    extensions::field<std::string, POD_DNS_CONFIG_OPTION_VALUE> value;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
