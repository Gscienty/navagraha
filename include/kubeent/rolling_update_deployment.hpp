#ifndef _NAVAGRAHA_KUBEENT_ROLLING_UPDATE_DEPLOYMENT_H
#define _NAVAGRAHA_KUBEENT_ROLLING_UPDATE_DEPLOYMENT_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char ROLLING_UPDATE_DEPLOYMENT_MAX_SURGE[];
extern char ROLLING_UPDATE_DEPLOYMENT_MAX_UNAVAILABLE[];

class rolling_update_deployment : public extensions::serializable<rolling_update_deployment> {
public:
    extensions::field<
        int,
        ROLLING_UPDATE_DEPLOYMENT_MAX_SURGE> max_surge;
    extensions::field<
        int, 
        ROLLING_UPDATE_DEPLOYMENT_MAX_UNAVAILABLE> max_unavailable;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
