#ifndef _NAVAGRAHA_KUBEENT_TIME_H
#define _NAVAGRAHA_KUBEENT_TIME_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char TIME_FIELD_EFFECT[];
extern char TIME_FIELD_KEY[];
extern char TIME_FIELD_TOLERATION_SECONDS[];
extern char TIME_FIELD_VALUE[];

class time : public extensions::serializable<time> {
public:
    extensions::field<std::string, TIME_FIELD_EFFECT> effect; 
    extensions::field<std::string, TIME_FIELD_KEY> key;
    extensions::field<int, TIME_FIELD_TOLERATION_SECONDS> toleration_seconds;
    extensions::field<std::string, TIME_FIELD_VALUE> value;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
