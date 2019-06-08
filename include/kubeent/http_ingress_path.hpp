#ifndef _NAVAGRAHA_KUBEENT_HTTP_INGRESS_PATH_H
#define _NAVAGRAHA_KUBEENT_HTTP_INGRESS_PATH_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/ingress_backend.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char HTTP_INGRESS_PATH_BACKEND[];
extern char HTTP_INGRESS_PATH_PATH[];

class http_ingress_path : public extensions::serializable<http_ingress_path> {
public:
    extensions::field<ingress_backend, HTTP_INGRESS_PATH_BACKEND> backend;
    extensions::field<std::string, HTTP_INGRESS_PATH_PATH> path;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
