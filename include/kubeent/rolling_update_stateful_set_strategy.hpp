#ifndef _NAVAGRAHA_KUBEENT_ROLLING_UPDATE_STATEFUL_SET_STRATEGY_H
#define _NAVAGRAHA_KUBEENT_ROLLING_UPDATE_STATEFUL_SET_STRATEGY_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/percentage_value.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ROLLING_UPDATE_STATEFUL_SET_STRATEGY_PARTITION[];

class rolling_update_stateful_set_strategy : public extensions::serializable<rolling_update_stateful_set_strategy> {
public:
    extensions::field<percentage_value, ROLLING_UPDATE_STATEFUL_SET_STRATEGY_PARTITION> partition;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
