#ifndef _NAVAGRAHA_KUBEENT_OBJECT_META_H
#define _NAVAGRAHA_KUBEENT_OBJECT_META_H

#include "extensions/field.hpp"
#include "extensions/object_wrapper.hpp"
#include "extensions/list_wrapper.hpp"
#include "kubeent/time.hpp"
#include "kubeent/initializers.hpp"

namespace navagraha {
namespace kubeent {

extern char OBJECT_META_ANNOTATIONS[];
extern char OBJECT_META_CLUSTER_NAME[];
extern char OBJECT_META_CREATION_TIMESTAMP[];
extern char OBJECT_META_DELETION_GRACE_PERIOD_SECONDS[];
extern char OBJECT_META_DELETION_TIMESTAMP[];
extern char OBJECT_META_FINALIZERS[];
extern char OBJECT_META_GENERATE_NAME[];
extern char OBJECT_META_GENERATION[];
extern char OBJECT_META_INITIALIZERS[];
extern char OBJECT_META_LABELS[];
extern char OBJECT_META_NAME[];
extern char OBJECT_META_NAMESPACE[];
extern char OBJECT_META_OWNER_REFERENCES[];
extern char OBJECT_META_RESOURCE_VERSION[];
extern char OBJECT_META_SELF_LINK[];
extern char OBJECT_META_UID[];

class object_meta {
public:
    extensions::field<extensions::object_wrapper, OBJECT_META_ANNOTATIONS> annotations;
    extensions::field<std::string, OBJECT_META_CLUSTER_NAME> cluster_name;
    extensions::field<time, OBJECT_META_CREATION_TIMESTAMP> creation_timestamp;
    extensions::field<int, OBJECT_META_DELETION_GRACE_PERIOD_SECONDS> deletion_grace_period_seconds;
    extensions::field<time, OBJECT_META_DELETION_TIMESTAMP> deletion_timestamp;
    extensions::field<extensions::list_wrapper, OBJECT_META_FINALIZERS> finalizers;
    extensions::field<std::string, OBJECT_META_GENERATE_NAME> generate_name;
    extensions::field<int, OBJECT_META_GENERATION> generation;
    extensions::field<initializers, OBJECT_META_INITIALIZERS> inits;
    extensions::field<extensions::object_wrapper, OBJECT_META_LABELS> labels;
    extensions::field<std::string, OBJECT_META_NAME> name;
    extensions::field<std::string, OBJECT_META_NAMESPACE> space;
    extensions::field<extensions::list_wrapper, OBJECT_META_OWNER_REFERENCES> owner_references;
    extensions::field<std::string, OBJECT_META_RESOURCE_VERSION> resource_version;
    extensions::field<std::string, OBJECT_META_SELF_LINK> self_link;
    extensions::field<std::string, OBJECT_META_UID> uid;

    static void serialize(object_meta & obj, std::ostringstream & str);
};

}
}

#endif
