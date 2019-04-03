#include "kubeent/empty_dir_volume_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char EMPTY_DIR_VOLUME_SOURCE_MEDIUM[] = "medium";
char EMPTY_DIR_VOLUME_SOURCE_SIZE_LIMIT[] = "sizeLimit";

void empty_dir_volume_source::serialize(empty_dir_volume_source & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.medium)
        .add(obj.size_limit)
        .serialize(str);
}
}
}
