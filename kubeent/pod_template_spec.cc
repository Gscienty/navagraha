#include "kubeent/pod_template_spec.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char POD_TEMPLATE_SPEC_METADATA[] = "metadata";
char POD_TEMPLATE_SPEC_SPEC[] = "spec";

void pod_template_spec::serialize(pod_template_spec & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.metadata)
        .add(obj.spec)
        .serialize(str);
}
}
}
