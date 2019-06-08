#ifndef _NAVAGRAHA_KUBEENT_REPLICATION_CONTROLLER_H
#define _NAVAGRAHA_KUBEENT_REPLICATION_CONTROLLER_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/replication_controller_spec.hpp"
#include "kubeent/replication_controller_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char REPLICATION_CONTROLLER_API_VERSION[];
extern char REPLICATION_CONTROLLER_KIND[];
extern char REPLICATION_CONTROLLER_METADATA[];
extern char REPLCIATION_CONTROLLER_SPEC[];
extern char REPLCIATION_CONTROLLER_STATUS[];


class replication_controller : public extensions::serializable<replication_controller> { 
public:
    extensions::field<std::string, REPLICATION_CONTROLLER_API_VERSION> api_version;
    extensions::field<std::string, REPLICATION_CONTROLLER_KIND> kind;
    extensions::field<object_meta, REPLICATION_CONTROLLER_METADATA> metadata;
    extensions::field<replication_controller_spec, REPLCIATION_CONTROLLER_SPEC> spec;
    extensions::field<replication_controller_status, REPLCIATION_CONTROLLER_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}


#endif
