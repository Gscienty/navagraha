#include "kubeent/downward_api_volume_file.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char DOWNWARD_API_VOLUME_FILE_FIELD_REF[] = "fieldRef";
char DOWNWARD_API_VOLUME_FILE_MODE[] = "mode";
char DOWNWARD_API_VOLUME_FILE_PATH[] = "path";
char DOWNWARD_API_VOLUME_FILE_RESOURCE_FIELD_REF[] = "fieldRef";

void downward_api_volume_file::serialize(downward_api_volume_file & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.field_ref)
        .add(obj.mode)
        .add(obj.path)
        .add(obj.resource_field_ref)
        .serialize(str);
}

}
}
