#ifndef _NAVAGRAHA_HTTP_CLIENT_CURL_HELPER_H
#define _NAVAGRAHA_HTTP_CLIENT_CURL_HELPER_H

#include "extensions/static_constructable.hpp"
#include "http_client/client.hpp"
#include <string>
#include <curl/curl.h>

namespace navagraha {
namespace http_client {

class curl_helper : public extensions::static_constructable<curl_helper> {
private:
    const std::string cert;
    const std::string key;
    const std::string ca;
    const std::string host;
    const std::string unix_socket;

public:
    static void static_construct();

    curl_helper(const std::string cert,
                const std::string key,
                const std::string ca,
                const std::string host);

    curl_helper(const std::string unix_socket);


    template <typename T> T build()
    {
        CURL * curl = curl_easy_init();

        curl_easy_setopt(curl, CURLOPT_CAINFO, this->ca.c_str());
        curl_easy_setopt(curl, CURLOPT_SSLCERT, this->cert.c_str());
        curl_easy_setopt(curl, CURLOPT_SSLKEY, this->key.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

        return T(curl, this->host);
    }

    template <typename T> T unix_socket_build()
    {
        CURL * curl = curl_easy_init();

        curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, this->unix_socket.c_str());

        return T(curl);
    }
};

}
}

#endif
