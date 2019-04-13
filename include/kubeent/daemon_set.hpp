#ifndef _NAVAGRAHA_KUBEENT_DAEMON_SET_H
#define _NAVAGRAHA_KUBEENT_DAEMON_SET_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/daemon_set_spec.hpp"
#include "kubeent/daemon_set_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char DAEMON_SET_API_VERSION[];
extern char DAEMON_SET_KIND[];
extern char DAEMON_SET_METADATA[];
extern char DAEMON_SET_SPEC[];
extern char DAEMON_SET_STATUS[];

class daemon_set : public serializable<daemon_set> {
public:
    extensions::field<std::string, DAEMON_SET_API_VERSION> api_version;
    extensions::field<std::string, DAEMON_SET_KIND> kind;
    extensions::field<object_meta, DAEMON_SET_METADATA> metadata;
    extensions::field<daemon_set_spec, DAEMON_SET_SPEC> spec;
    extensions::field<daemon_set_status, DAEMON_SET_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
