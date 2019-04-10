#include "kubeent/downward_api_volume_file.hpp"

namespace navagraha {
namespace kubeent {

char DOWNWARD_API_VOLUME_FILE_FIELD_REF[] = "fieldRef";
char DOWNWARD_API_VOLUME_FILE_MODE[] = "mode";
char DOWNWARD_API_VOLUME_FILE_PATH[] = "path";
char DOWNWARD_API_VOLUME_FILE_RESOURCE_FIELD_REF[] = "fieldRef";

void downward_api_volume_file::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->field_ref)
        .add(this->mode)
        .add(this->path)
        .add(this->resource_field_ref);
}

}
}
