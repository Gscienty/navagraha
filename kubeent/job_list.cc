#include "kubeent/job_list.hpp"

namespace navagraha {
namespace kubeent {

char JOB_LIST_API_VERSION[] = "apiVersion";
char JOB_LIST_ITEMS[] = "items";
char JOB_LIST_KIND[] = "kind";
char JOB_LIST_METADATA[] = "metadata";

void job_list::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->items)
        .add(this->kind)
        .add(this->metadata);
}

}
}
