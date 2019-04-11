#include "kubeent/object_meta.hpp"
#include <list>
#include <functional>
#include <algorithm>

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

void object_meta::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->annotations)
        .add(this->cluster_name)
        .add(this->creation_timestamp)
        .add(this->deletion_grace_period_seconds)
        .add(this->deletion_timestamp)
        .add(this->finalizers)
        .add(this->generate_name)
        .add(this->generation)
        .add(this->inits)
        .add(this->labels)
        .add(this->name)
        .add(this->owner_references)
        .add(this->resource_version)
        .add(this->self_link)
        .add(this->space)
        .add(this->uid);
}

}
}
