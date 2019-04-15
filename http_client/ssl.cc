#include "http_client/ssl.hpp"
#include <iostream>

namespace navagraha {
namespace http {


void ssl::static_construct()
{
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    ERR_load_CRYPTO_strings();
}

ssl::ssl(const std::string cert, const std::string key, const std::string ca)
    : ctx(SSL_CTX_new(TLSv1_2_client_method()))
    , ca(SSL_load_client_CA_file(ca.c_str()))
{
    SSL_CTX_set_options(this->ctx,
                        SSL_OP_ALL
                        | SSL_OP_NO_SSLv2
                        | SSL_OP_NO_SSLv3
                        | SSL_OP_NO_COMPRESSION
                        | SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION);
    SSL_CTX_set_ecdh_auto(this->ctx, 1);

    if (SSL_CTX_use_certificate_file(this->ctx, cert.c_str(), SSL_FILETYPE_PEM) != 1) {
        exit(-1);
    }

    if (SSL_CTX_use_PrivateKey_file(this->ctx, key.c_str(), SSL_FILETYPE_PEM) != 1) {
        exit(-2);
    }

    if (SSL_CTX_check_private_key(this->ctx) != 1) {
        exit(-3);
    }

    SSL_CTX_set_client_CA_list(this->ctx, this->ca);
}

ssl::~ssl()
{
    SSL_CTX_free(this->ctx);
    sk_X509_NAME_free(this->ca);
}

}
}
