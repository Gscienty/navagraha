#ifndef _NAVAGRAHA_KUBEENT_LOAD_BALANCER_STATUS_H
#define _NAVAGRAHA_KUBEENT_LOAD_BALANCER_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/load_balancer_ingress.hpp"

namespace navagraha {
namespace kubeent {

extern char LOAD_BALANCER_STATUS_INGRESS[];

class load_balancer_status : public extensions::serializable<load_balancer_status> {
public:
    extensions::field<
        extensions::special_list<load_balancer_ingress>,
        LOAD_BALANCER_STATUS_INGRESS> ingress;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
