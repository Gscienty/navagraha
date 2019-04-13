#ifndef _NAVAGRAHA_KUBEENT_SERVICE_STATUS_H
#define _NAVAGRAHA_KUBEENT_SERVICE_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/load_balancer_status.hpp"

namespace navagraha {
namespace kubeent {

extern char SERVICE_STATUS_LOAD_BALANCER[];

class service_status : public serializable<service_status> {
public:
    extensions::field<load_balancer_status, SERVICE_STATUS_LOAD_BALANCER> load_balancer;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
