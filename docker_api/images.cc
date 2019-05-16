#include "docker_api/images.hpp"
#include "extensions/tar.hpp"

namespace navagraha {
namespace docker_api {


images::images(CURL * curl)
    : http_client::unix_socket_client(curl)
{

}


extensions::special_list<dockerent::image> images::list()
{
    return this->get_call<extensions::special_list<dockerent::image>>("/images/json");
}

extensions::common_object images::create(std::string path, std::string tag)
{
    this->set_content_type("application/x-tar");
    std::string binary_payload;
    extensions::tar tar("/tmp/__dockerbuild.tar", path);
    tar();
    tar.extract(binary_payload);
    this->set_binary_content(binary_payload);
    return this->post_call<extensions::common_object>("/build?dockerfile=.%2FDockerfile"
                                                      "&t="
                                                      + tag);
}

}
}
