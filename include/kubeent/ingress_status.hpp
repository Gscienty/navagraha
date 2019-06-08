#ifndef _NAVAGRAHA_KUBEENT_INGRESS_STATUS_H
#define _NAVAGRAHA_KUBEENT_INGRESS_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/load_balancer_status.hpp"

namespace navagraha {
namespace kubeent {

extern char INGRESS_STATUS_LOAD_BALANCER[];

class ingress_status : public extensions::serializable<ingress_status> {
public:
    extensions::field<load_balancer_status, INGRESS_STATUS_LOAD_BALANCER> load_balancer;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
