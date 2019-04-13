#ifndef _NAVAGRAHA_KUBEENT_STATEFUL_SET_UPDATE_STRATEGY_H
#define _NAVAGRAHA_KUBEENT_STATEFUL_SET_UPDATE_STRATEGY_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/rolling_update_stateful_set_strategy.hpp"

namespace navagraha {
namespace kubeent {

extern char STATEFUL_SET_UPDATE_STRATEGY_ROLLING_UPDATE[];
extern char STATEFUL_SET_UPDATE_STRATEGY_TYPE[];

class stateful_set_update_strategy : public serializable<stateful_set_update_strategy> {
public:
    extensions::field<
        rolling_update_stateful_set_strategy,
        STATEFUL_SET_UPDATE_STRATEGY_ROLLING_UPDATE> rolling_update;
    extensions::field<std::string, STATEFUL_SET_UPDATE_STRATEGY_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
