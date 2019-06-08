#ifndef _NAVAGRAHA_KUBEENT_DAEMON_SET_UPDATE_STRATEGY_H
#define _NAVAGRAHA_KUBEENT_DAEMON_SET_UPDATE_STRATEGY_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/rolling_update_daemon_set.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char DAEMON_SET_UPDATE_STRATEGY_ROLLING_UPDATE[];
extern char DAEMON_SET_UPDATE_STRATEGY_TYPE[];

class daemon_set_update_strategy : public extensions::serializable<daemon_set_update_strategy> {
public:
    extensions::field<
        rolling_update_daemon_set,
        DAEMON_SET_UPDATE_STRATEGY_ROLLING_UPDATE> rolling_update;
    extensions::field<std::string, DAEMON_SET_UPDATE_STRATEGY_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
