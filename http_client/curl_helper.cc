#include "http_client/curl_helper.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>

#include <iostream>

namespace navagraha {
namespace http_client {

curl_helper::curl_helper(const std::string cert,
                         const std::string key,
                         const std::string ca,
                         const std::string base_uri)
    : cert(cert)
    , key(key)
    , ca(ca)
    , base_uri(base_uri)
{

}

void curl_helper::static_construct()
{
    curl_global_init(CURL_GLOBAL_SSL);
}

}
}
