#ifndef _NAVAGRAHA_DOCKER_API_IMAGES_H
#define _NAVAGRAHA_DOCKER_API_IMAGES_H

#include "http_client/client.hpp"
#include "extensions/special_list.hpp"
#include "dockerent/image.hpp"
#include <string>

namespace navagraha {
namespace docker_api {

class images : public http_client::client {
public:
    images(CURL * curl, const std::string host);

    images(CURL * curl);

    extensions::special_list<dockerent::image> list();

    extensions::common_object create(std::string path, std::string tag);
};

}
}

#endif
