#include "kubeent/preferred_scheduling_term.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char PREFERRED_SCHEDULING_TERM_PREFERENCE[] = "preference";
char PREFERRED_SCHEDULING_TERM_WEIGHT[] = "weight";

void preferred_scheduling_term::serialize(preferred_scheduling_term & obj,
                                         std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.perference)
        .add(obj.weight)
        .serialize(str);
}

}
}
