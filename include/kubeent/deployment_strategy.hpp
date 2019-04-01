#ifndef _NAVAGRAHA_KUBEENT_DEPLOYMENT_STRATEGY_H
#define _NAVAGRAHA_KUBEENT_DEPLOYMENT_STRATEGY_H

#include "extensions/field.hpp"
#include "kubeent/rolling_update_deployment.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char DEPLOYMENT_STRATEGY_ROLLING_UPDATE[];
extern char DEPLOYMENT_STRATEGY_TYPE[];

class deployment_strategy {
public:
    extensions::field<
        rolling_update_deployment,
        DEPLOYMENT_STRATEGY_ROLLING_UPDATE> rolling_update;
    extensions::field<
        std::string,
        DEPLOYMENT_STRATEGY_TYPE> type;

    static void serialize(deployment_strategy & obj, std::ostringstream & str);
};

}
}

#endif
