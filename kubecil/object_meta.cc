#include "kubecil/object_meta.hpp"
#include <list>
#include <functional>
#include <algorithm>

namespace navagraha {
namespace kubecil {

char OBJECT_META_ANNOTATIONS[] = "annotations";
char OBJECT_META_CLUSTER_NAME[] = "clusterName";
char OBJECT_META_CREATION_TIMESTAMP[] = "creationTimestamp";
char OBJECT_META_DELETION_GRACE_PERIOD_SECONDS[] = "deletionGracePeriodSeconds";
char OBJECT_META_DELETION_TIMESTAMP[] = "deletionTimestamp";
char OBJECT_META_FINALIZERS[] = "finalizers";
char OBJECT_META_GENERATE_NAME[] = "generateName";
char OBJECT_META_GENERATION[] = "generation";
char OBJECT_META_INITIALIZERS[] = "initializers";
char OBJECT_META_LABELS[] = "labels";
char OBJECT_META_NAME[] = "name";
char OBJECT_META_NAMESPACE[] = "namespace";
char OBJECT_META_OWNER_REFERENCES[] = "ownerReferences";
char OBJECT_META_RESOURCE_VERSION[] = "resourceVersion";
char OBJECT_META_SELF_LINK[] = "selfLink";
char OBJECT_META_UID[] = "uid";

void object_meta::serialize(object_meta & obj, std::ostringstream & str)
{
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> serializers = {
        extensions::field_serializer(obj.annotations),
        extensions::field_serializer(obj.cluster_name),
        extensions::field_serializer(obj.creation_timestamp),
        extensions::field_serializer(obj.deletion_grace_period_seconds),
        extensions::field_serializer(obj.deletion_timestamp),
        extensions::field_serializer(obj.finalizers),
        extensions::field_serializer(obj.generate_name),
        extensions::field_serializer(obj.generation),
        extensions::field_serializer(obj.inits),
        extensions::field_serializer(obj.labels),
        extensions::field_serializer(obj.name),
        extensions::field_serializer(obj.owner_references),
        extensions::field_serializer(obj.resource_version),
        extensions::field_serializer(obj.self_link),
        extensions::field_serializer(obj.space),
        extensions::field_serializer(obj.uid)
    };

    str.put('{');
    extensions::fields_serialize(serializers, str);
    str.put('}');

}

}
}
