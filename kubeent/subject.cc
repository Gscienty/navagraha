#include "kubeent/subject.hpp"

namespace navagraha {
namespace kubeent {

char SUBJECT_API_GROUP[] = "apiGroup";
char SUBJECT_KIND[] = "kind";
char SUBJECT_NAME[] = "name";
char SUBJECT_NAMESPACE[] = "namespace";

void subject::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_group)
        .add(this->kind)
        .add(this->name)
        .add(this->namespace_);
}

}
}
