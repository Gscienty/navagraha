#ifndef _NAVAGRAHA_KUBEENT_PERSISTENT_VOLUME_CLAIM_STATUS_H
#define _NAVAGRAHA_KUBEENT_PERSISTENT_VOLUME_CLAIM_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/common_object.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/persistent_volume_claim_condition.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char PERSISTENT_VOLUME_CLAIM_STATUS_ACCESS_MODES[];
extern char PERSISTENT_VOLUME_CLAIM_STATUS_CAPACITY[];
extern char PERSISTENT_VOLUME_CLAIM_CONDITIONS[];
extern char PERSISTENT_VOLUME_CLAIM_PHASE[];

class persistent_volume_claim_status : public serializable<persistent_volume_claim_status> {
public:
    extensions::field<
        extensions::special_list<std::string>,
        PERSISTENT_VOLUME_CLAIM_STATUS_ACCESS_MODES> access_modes;
    extensions::field<
        extensions::common_object,
        PERSISTENT_VOLUME_CLAIM_STATUS_CAPACITY> capacity;
    extensions::field<
        extensions::special_list<persistent_volume_claim_condition>,
        PERSISTENT_VOLUME_CLAIM_CONDITIONS> conditions;
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_PHASE> phase;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
