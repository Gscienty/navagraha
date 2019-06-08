#ifndef _NAVAGRAHA_KUBEENT_SECRET_ENV_SOURCE_H
#define _NAVAGRAHA_KUBEENT_SECRET_ENV_SOURCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SECURITY_ENV_SOURCE_NAME[];
extern char SECURITY_ENV_SOURCE_OPTIONAL[];

class secret_env_source : public extensions::serializable<secret_env_source> {
public:
    extensions::field<std::string, SECURITY_ENV_SOURCE_NAME> name;
    extensions::field<bool, SECURITY_ENV_SOURCE_OPTIONAL> optional;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
