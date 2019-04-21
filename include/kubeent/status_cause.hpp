#ifndef _NAVAGRAHA_KUBEENT_STATUS_CAUSE_H
#define _NAVAGRAHA_KUBEENT_STATUS_CAUSE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char STATUS_CAUSE_FIELD[];
extern char STATUS_CAUSE_MESSAGE[];
extern char STATUS_CAUSE_REASON[];

class status_cause : public serializable<status_cause> {
public:
    extensions::field<std::string, STATUS_CAUSE_FIELD> field;
    extensions::field<std::string, STATUS_CAUSE_MESSAGE> message;
    extensions::field<std::string, STATUS_CAUSE_REASON> reason;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
