#include "kubeent/prefered_scheduling_term.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char PREFERED_SCHEDULING_TERM_PERFERENCE[] = "preference";
char PREFERED_SCHEDULING_TERM_WEIGHT[] = "weight";

void prefered_scheduling_term::serialize(prefered_scheduling_term & obj,
                                         std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.perference)
        .add(obj.weight)
        .serialize(str);
}

}
}
