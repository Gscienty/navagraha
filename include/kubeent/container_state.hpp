#ifndef _NAVAGRAHA_KUBEENT_CONTAINER_STATE_H
#define _NAVAGRAHA_KUBEENT_CONTAINER_STATE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/container_state_running.hpp"
#include "kubeent/container_state_terminated.hpp"
#include "kubeent/container_state_waiting.hpp"

namespace navagraha {
namespace kubeent {

extern char CONTAINER_STATE_RUNNING[];
extern char CONTAINER_STATE_TERMINATED[];
extern char CONTAINER_STATE_WAITING[];

class container_state : public extensions::serializable<container_state> {
public:
    extensions::field<container_state_running, CONTAINER_STATE_RUNNING> running;
    extensions::field<container_state_terminated, CONTAINER_STATE_TERMINATED> terminated;
    extensions::field<container_state_waiting, CONTAINER_STATE_WAITING> waiting;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
