#ifndef _NAVAGRAHA_KUBEENT_INGRESS_TLS_H
#define _NAVAGRAHA_KUBEENT_INGRESS_TLS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char INGRESS_TLS_HOSTS[];
extern char INGRESS_TLS_SECRET_NAME[];

class ingress_tls : public serializable<ingress_tls> {
public:
    extensions::field<extensions::special_list<std::string>, INGRESS_TLS_HOSTS> hosts;
    extensions::field<std::string, INGRESS_TLS_SECRET_NAME> secret_name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
