#ifndef _NAVAGRAHA_KUBEENT_CONTAINER_STATE_WAITING_H
#define _NAVAGRAHA_KUBEENT_CONTAINER_STATE_WAITING_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CONTAINER_STATE_WAITING_MESSAGE[];
extern char CONTAINER_STATE_WAITING_REASON[];

class container_state_waiting : public serializable<container_state_waiting> {
public:
    extensions::field<std::string, CONTAINER_STATE_WAITING_MESSAGE> message;
    extensions::field<std::string, CONTAINER_STATE_WAITING_REASON> reason;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
