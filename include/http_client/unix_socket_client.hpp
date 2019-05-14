#ifndef _NAVAGRAHA_HTTP_CLIENT_UNIX_SOCKET_CLIENT_H
#define _NAVAGRAHA_HTTP_CLIENT_UNIX_SOCKET_CLIENT_H

#include "http_client/client.hpp"

namespace navagraha {
namespace http_client {

class unix_socket_client : public client {
public:
    unix_socket_client(CURL * curl) : client(curl, "http://localhost") { }
};

}
}

#endif
