#ifndef _NAVAGRAHA_KUBEENT_CONTAINER_STATE_RUNNING_H
#define _NAVAGRAHA_KUBEENT_CONTAINER_STATE_RUNNING_H

#include "extensions/serializer_helper.hpp"
#include "extensions/field.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/time.hpp"

namespace navagraha {
namespace kubeent {

extern char CONTAINER_STATE_RUNNING_STARTED_AT[];

class container_state_running : public extensions::serializable<container_state_running> {
public:
    extensions::field<time, CONTAINER_STATE_RUNNING_STARTED_AT> started_at;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
