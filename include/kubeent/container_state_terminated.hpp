#ifndef _NAVAGRAHA_KUBEENT_CONTAINER_STATE_TERMINATED_H
#define _NAVAGRAHA_KUBEENT_CONTAINER_STATE_TERMINATED_H

#include "extensions/serializer_helper.hpp"
#include "extensions/field.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/time.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CONTAINER_STATE_TERMINATED_CONTAINER_ID[];
extern char CONTAINER_STATE_TERMINATED_EXIT_CODE[];
extern char CONTAINER_STATE_TERMINATED_FINISHED_AT[];
extern char CONTAINER_STATE_TERMINATED_MESSAGE[];
extern char CONTAINER_STATE_TERMINATED_REASON[];
extern char CONTAINER_STATE_TERMINATED_SIGNAL[];
extern char CONTAINER_STATE_TERMINATED_STARTED_AT[];

class container_state_terminated : public serializable<container_state_terminated> {
public:
    extensions::field<std::string, CONTAINER_STATE_TERMINATED_CONTAINER_ID> container_id;
    extensions::field<int, CONTAINER_STATE_TERMINATED_EXIT_CODE> exit_code;
    extensions::field<time, CONTAINER_STATE_TERMINATED_FINISHED_AT> finished_at;
    extensions::field<std::string, CONTAINER_STATE_TERMINATED_MESSAGE> message;
    extensions::field<std::string, CONTAINER_STATE_TERMINATED_REASON> reason;
    extensions::field<int, CONTAINER_STATE_TERMINATED_SIGNAL> signal;
    extensions::field<time, CONTAINER_STATE_TERMINATED_STARTED_AT> started_at;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
