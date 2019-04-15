#ifndef _NAVAGRAHA_HTTP_SSL_H
#define _NAVAGRAHA_HTTP_SSL_H

#include "extensions/static_constructable.hpp"
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <string>

namespace navagraha {
namespace http {

class ssl : public extensions::static_constructable<ssl> {
private:
    SSL_CTX * ctx;
    STACK_OF(X509_NAME) * ca;
public:
    static void static_construct();

    ssl(const std::string cert, const std::string key, const std::string ca);

    virtual ~ssl();
};

}
}

#endif
