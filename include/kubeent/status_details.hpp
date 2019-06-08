#ifndef _NAVAGRAHA_KUBEENT_STATUS_DETAILS_H
#define _NAVAGRAHA_KUBEENT_STATUS_DETAILS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/status_cause.hpp"

namespace navagraha {
namespace kubeent {

extern char STATUS_DETAILS_CAUSES[];
extern char STATUS_DETAILS_GROUP[];
extern char STATUS_DETAILS_KIND[];
extern char STATUS_DETAILS_NAME[];
extern char STATUS_DETAILS_RETRY_AFTER_SECONDS[];
extern char STATUS_DETAILS_UID[];

class status_details : public extensions::serializable<status_details> {
public:
    extensions::field<
        extensions::special_list<status_cause>, STATUS_DETAILS_CAUSES> causes;
    extensions::field<std::string, STATUS_DETAILS_GROUP> group;
    extensions::field<std::string, STATUS_DETAILS_KIND> kind;
    extensions::field<std::string, STATUS_DETAILS_NAME> name;
    extensions::field<int, STATUS_DETAILS_RETRY_AFTER_SECONDS> retry_after_seconds;
    extensions::field<std::string, STATUS_DETAILS_UID> uid;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
