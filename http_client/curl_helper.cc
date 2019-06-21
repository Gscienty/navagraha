#include "http_client/curl_helper.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>

namespace navagraha {
namespace http_client {

curl_helper::curl_helper(const std::string cert,
                         const std::string key,
                         const std::string ca,
                         const std::string host)
    : cert(cert)
    , key(key)
    , ca(ca)
    , host(host)
{

}

curl_helper::curl_helper(const std::string unix_socket)
    : unix_socket(unix_socket)
{

}

void curl_helper::static_construct()
{
    curl_global_init(CURL_GLOBAL_SSL);
}

}
}
