#ifndef _NAVAGRAHA_HTTP_CLIENT_SIMPLE_CLIENT_H
#define _NAVAGRAHA_HTTP_CLIENT_SIMPLE_CLIENT_H

#include "http_client/client.hpp"

namespace navagraha {
namespace http_client {

class simple_client : protected client {
public:
    simple_client(CURL * curl, const std::string host);

    http_response post_request(const std::string path, std::string payload);
};

}
}

#endif
