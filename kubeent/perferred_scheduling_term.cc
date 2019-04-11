#include "kubeent/preferred_scheduling_term.hpp"

namespace navagraha {
namespace kubeent {

char PREFERRED_SCHEDULING_TERM_PREFERENCE[] = "preference";
char PREFERRED_SCHEDULING_TERM_WEIGHT[] = "weight";

void preferred_scheduling_term::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->perference)
        .add(this->weight);
}

}
}
