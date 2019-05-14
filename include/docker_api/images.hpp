#ifndef _NAVAGRAHA_DOCKER_API_IMAGES_H
#define _NAVAGRAHA_DOCKER_API_IMAGES_H

#include "http_client/unix_socket_client.hpp"
#include "extensions/common_list.hpp"

namespace navagraha {
namespace docker_api {

class images : public http_client::unix_socket_client {
public:
    images(CURL * curl);

    extensions::common_list read();
};

}
}

#endif
