#include "kubeent/deployment.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char DEPLOYMENT_API_VERSION[] = "apiVersion";
char DEPLOYMENT_KIND[] = "kind";
char DEPLOYMENT_METADATA[] = "metadata";
char DEPLOYMENT_SPEC[] = "spec";
char DEPLOYMENT_STATUS[] = "status";

void deployment::serialize(deployment & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.api_version)
        .add(obj.kind)
        .add(obj.metadata)
        .add(obj.spec)
        .add(obj.status)
        .serialize(str);
}

}
}
