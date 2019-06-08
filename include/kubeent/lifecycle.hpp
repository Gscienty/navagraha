#ifndef _NAVAGRAHA_KUBEENT_LIFECYCLE_H
#define _NAVAGRAHA_KUBEENT_LIFECYCLE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/handler.hpp"

namespace navagraha {
namespace kubeent {

extern char LIFECYCLE_POST_START[];
extern char LIFECYCLE_PRE_STOP[];

class lifecycle : public extensions::serializable<lifecycle> {
public:
    extensions::field<handler, LIFECYCLE_POST_START> post_start;
    extensions::field<handler, LIFECYCLE_PRE_STOP> pre_stop;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
