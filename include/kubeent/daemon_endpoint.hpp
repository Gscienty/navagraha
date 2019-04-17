#ifndef _NAVAGRAHA_KUBEENT_DAEMON_ENDPOINT_H
#define _NAVAGRAHA_KUBEENT_DAEMON_ENDPOINT_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char DAEMON_ENDPOINT_PORT[];

class daemon_endpoint : public serializable<daemon_endpoint> {
public:
    extensions::field<int, DAEMON_ENDPOINT_PORT> port;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
