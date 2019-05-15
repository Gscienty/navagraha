#include "dockerent/image.hpp"

namespace navagraha {
namespace dockerent {

char IMAGE_ID[] = "Id";
char IMAGE_PARENT_ID[] = "ParentId";
char IMAGE_REPO_TAGS[] = "RepoTags";
char IMAGE_REPO_DIGESTS[] = "RepoDigests";
char IMAGE_CREATED[] = "Created";
char IMAGE_SIZE[] = "Size";
char IMAGE_SHARED_SIZE[] = "SharedSize";
char IMAGE_VIRTUAL_SIZE[] = "VirtualSize";
char IMAGE_LABELS[] = "Labels";
char IMAGE_CONTAINERS[] = "Containers";

void image::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->id)
        .add(this->parent_id)
        .add(this->repo_tags)
        .add(this->repo_digests)
        .add(this->created)
        .add(this->size)
        .add(this->shared_size)
        .add(this->virtual_size)
        .add(this->labels)
        .add(this->containers);
}

}
}
