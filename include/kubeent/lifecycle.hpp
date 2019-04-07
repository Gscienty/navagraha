#ifndef _NAVAGRAHA_KUBEENT_LIFECYCLE_H
#define _NAVAGRAHA_KUBEENT_LIFECYCLE_H

#include "extensions/field.hpp"
#include "kubeent/handler.hpp"

namespace navagraha {
namespace kubeent {

extern char LIFECYCLE_POST_START[];
extern char LIFECYCLE_PRE_STOP[];

class lifecycle {
public:
    extensions::field<handler, LIFECYCLE_POST_START> post_start;
    extensions::field<handler, LIFECYCLE_PRE_STOP> pre_stop;

    static void serialize(lifecycle & obj, std::ostringstream & str);
};

}
}

#endif
