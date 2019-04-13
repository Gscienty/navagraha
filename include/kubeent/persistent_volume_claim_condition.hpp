#ifndef _NAVAGRAHA_KUBEENT_PERSISTENT_VOLUME_CLAIM_CONDITION_H
#define _NAVAGRAHA_KUBEENT_PERSISTENT_VOLUME_CLAIM_CONDITION_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/time.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char PERSISTENT_VOLUME_CLAIM_CONDITION_LAST_PROBE_TIME[];
extern char PERSISTENT_VOLUME_CLAIM_CONDITION_LAST_TRANSITION_TIME[];
extern char PERSISTENT_VOLUME_CLAIM_CONDITION_MESSAGE[];
extern char PERSISTENT_VOLUME_CLAIM_CONDITION_REASON[];
extern char PERSISTENT_VOLUME_CLAIM_CONDITION_STATUS[];
extern char PERSISTENT_VOLUME_CLAIM_CONDITION_TYPE[];

class persistent_volume_claim_condition : public serializable<persistent_volume_claim_condition> {
public:
    extensions::field<time, PERSISTENT_VOLUME_CLAIM_CONDITION_LAST_PROBE_TIME> last_probe_time;
    extensions::field<time, PERSISTENT_VOLUME_CLAIM_CONDITION_LAST_TRANSITION_TIME> last_transition_time;
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_CONDITION_MESSAGE> message;
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_CONDITION_REASON> reason;
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_CONDITION_STATUS> status;
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_CONDITION_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
