#ifndef _NAVAGRAHA_KUBEENT_TAINT_H
#define _NAVAGRAHA_KUBEENT_TAINT_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/time.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char TAINT_EFFECT[];
extern char TAINT_KEY[];
extern char TAINT_TIME_ADDED[];
extern char TAINT_VALUE[];

class taint : public serializable<taint> {
public:
    extensions::field<std::string, TAINT_EFFECT> effect;
    extensions::field<std::string, TAINT_KEY> key;
    extensions::field<time, TAINT_TIME_ADDED> time_added;
    extensions::field<std::string, TAINT_VALUE> value;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
