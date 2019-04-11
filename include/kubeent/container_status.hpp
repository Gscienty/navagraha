#ifndef _NAVAGRAHA_KUBEENT_CONTAINER_STATUS_H
#define _NAVAGRAHA_KUBEENT_CONTAINER_STATUS_H

#include "extensions/serializer_helper.hpp"
#include "extensions/field.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/container_state.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CONTAINER_STATUS_CONTAINER_ID[];
extern char CONTAINER_STATUS_IMAGE[];
extern char CONTAINER_STATUS_IMAGE_ID[];
extern char CONTAINER_STATUS_LAST_STATE[];
extern char CONTAINER_STATUS_NAME[];
extern char CONTAINER_STATUS_READY[];
extern char CONTAINER_STATUS_RESTART_COUNT[];
extern char CONTAINER_STATUS_STATE[];

class container_status : public serializable<container_status> {
public:
    extensions::field<std::string, CONTAINER_STATUS_CONTAINER_ID> container_id;
    extensions::field<std::string, CONTAINER_STATUS_IMAGE> image;
    extensions::field<std::string, CONTAINER_STATUS_IMAGE_ID> image_id;
    extensions::field<container_state, CONTAINER_STATUS_LAST_STATE> last_state;
    extensions::field<std::string, CONTAINER_STATUS_NAME> name;
    extensions::field<bool, CONTAINER_STATUS_READY> ready;
    extensions::field<int, CONTAINER_STATUS_RESTART_COUNT> restart_count;
    extensions::field<container_state, CONTAINER_STATUS_STATE> state;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
