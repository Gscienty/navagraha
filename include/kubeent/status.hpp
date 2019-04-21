#ifndef _NAVAGRAHA_KUBEENT_STATUS_H
#define _NAVAGRAHA_KUBEENT_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/status_details.hpp"
#include "kubeent/list_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char STATUS_API_VERSION[];
extern char STATUS_CODE[];
extern char STATUS_DETAILS[];
extern char STATUS_KIND[];
extern char STATUS_MESSAGE[];
extern char STATUS_METADATA[];
extern char STATUS_REASON[];
extern char STATUS_STATUS[];

class status : public serializable<status> {
public:
    extensions::field<std::string, STATUS_API_VERSION> api_version;
    extensions::field<int, STATUS_CODE> code;
    extensions::field<status_details, STATUS_DETAILS> details;
    extensions::field<std::string, STATUS_KIND> kind;
    extensions::field<std::string, STATUS_MESSAGE> message;
    extensions::field<list_meta, STATUS_METADATA> metadata;
    extensions::field<std::string, STATUS_REASON> reason;
    extensions::field<std::string, STATUS_STATUS> status_;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
