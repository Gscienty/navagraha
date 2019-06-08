#ifndef _NAVAGRAHA_KUBEENT_SESSION_AFFINITY_CONFIG_H
#define _NAVAGRAHA_KUBEENT_SESSION_AFFINITY_CONFIG_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/client_ip_config.hpp"

namespace navagraha {
namespace kubeent {

extern char SESSION_AFFINITY_CONFIG_CLIENT_IP[];

class session_affinity_config : public extensions::serializable<session_affinity_config> {
public:
    extensions::field<client_ip_config, SESSION_AFFINITY_CONFIG_CLIENT_IP> client_ip;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
