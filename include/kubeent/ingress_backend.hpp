#ifndef _NAVAGRAHA_KUBEENT_INGRESS_BACKEND_H
#define _NAVAGRAHA_KUBEENT_INGRESS_BACKEND_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char INGRESS_BACKEND_SERVICE_NAME[];
extern char INGRESS_BACKEDN_SERVICE_PORT[];

class ingress_backend : public extensions::serializable<ingress_backend> {
public:
    extensions::field<std::string, INGRESS_BACKEND_SERVICE_NAME> service_name;
    extensions::field<int, INGRESS_BACKEDN_SERVICE_PORT> service_port;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
