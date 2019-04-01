#include "kubeent/object_meta.hpp"
#include <list>
#include <functional>
#include <algorithm>
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

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
    extensions::link_serializer()
        .add(obj.annotations)
        .add(obj.cluster_name)
        .add(obj.creation_timestamp)
        .add(obj.deletion_grace_period_seconds)
        .add(obj.deletion_timestamp)
        .add(obj.finalizers)
        .add(obj.generate_name)
        .add(obj.generation)
        .add(obj.inits)
        .add(obj.labels)
        .add(obj.name)
        .add(obj.owner_references)
        .add(obj.resource_version)
        .add(obj.self_link)
        .add(obj.space)
        .add(obj.uid)
        .serialize(str);
}

}
}
