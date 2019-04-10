#ifndef _NAVAGRAHA_KUBEENT_TOLERATION_H
#define _NAVAGRAHA_KUBEENT_TOLERATION_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char TOLERATION_EFFECT[];
extern char TOLERATION_KEY[];
extern char TOLERATION_OPERATOR[];
extern char TOLERATION_TOLERATION_SECONDS[];
extern char TOLERATION_VALUE[];

class toleration : public serializable<toleration> {
public:
    extensions::field<std::string, TOLERATION_EFFECT> effect;
    extensions::field<std::string, TOLERATION_KEY> key;
    extensions::field<std::string, TOLERATION_OPERATOR> operator_;
    extensions::field<int, TOLERATION_TOLERATION_SECONDS> toleration_seconds;
    extensions::field<std::string, TOLERATION_VALUE> value;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
