#ifndef _NAVAGRAHA_KUBEENT_LOAD_BALANCER_INGRESS_H
#define _NAVAGRAHA_KUBEENT_LOAD_BALANCER_INGRESS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char LOAD_BALANCER_INGRESS_HOSTNAME[];
extern char LOAD_BALANCER_INGRESS_IP[];

class load_balancer_ingress : public serializable<load_balancer_ingress> {
public:
    extensions::field<std::string, LOAD_BALANCER_INGRESS_HOSTNAME> hostname;
    extensions::field<std::string, LOAD_BALANCER_INGRESS_IP> ip;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
