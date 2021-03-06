#ifndef _NAVAGRAHA_KUBEENT_ROLLING_UPDATE_DAEMON_SET_H
#define _NAVAGRAHA_KUBEENT_ROLLING_UPDATE_DAEMON_SET_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/percentage_value.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ROLLING_UPDATE_DAEMON_SET_MAX_UNAVAILABLE[];

class rolling_update_daemon_set : public extensions::serializable<rolling_update_daemon_set> {
public:
    extensions::field<percentage_value, ROLLING_UPDATE_DAEMON_SET_MAX_UNAVAILABLE> max_unavailable;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
