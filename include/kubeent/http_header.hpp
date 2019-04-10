#ifndef _NAVAGRAHA_KUBEENT_HTTP_HEADER_H
#define _NAVAGRAHA_KUBEENT_HTTP_HEADER_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char HTTP_HEADER_NAME[];
extern char HTTP_HEADER_VALUE[];

class http_header : public serializable<http_header> {
public:
    extensions::field<std::string, HTTP_HEADER_NAME> name;
    extensions::field<std::string, HTTP_HEADER_VALUE> value;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
