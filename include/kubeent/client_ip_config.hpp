#ifndef _NAVAGRAHA_KUBEENT_CLIENT_IP_CONFIG_H
#define _NAVAGRAHA_KUBEENT_CLIENT_IP_CONFIG_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char CLIENT_IP_CONFIG_TIMEOUT_SECONDS[];

class client_ip_config : public serializable<client_ip_config> {
public:
    extensions::field<int, CLIENT_IP_CONFIG_TIMEOUT_SECONDS> timeout_seconds;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
