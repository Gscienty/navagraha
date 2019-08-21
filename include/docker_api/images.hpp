#ifndef _NAVAGRAHA_DOCKER_API_IMAGES_H
#define _NAVAGRAHA_DOCKER_API_IMAGES_H

#include "http_client/client.hpp"
#include "http_client/http_response.hpp"
#include "dockerent/image.hpp"
#include <string>

namespace navagraha {
namespace docker_api {

class images : public http_client::client {
public:
    images(CURL * curl, const std::string host);

    images(CURL * curl);

    http_client::http_response list();

    http_client::http_response create(std::string path, std::string tag, std::function<void (std::string &)> cb);

    http_client::http_response delete_builder_cache();

    http_client::http_response remove(std::string name);
};

}
}

#endif
