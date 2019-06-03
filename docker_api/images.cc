#include "docker_api/images.hpp"
#include "extensions/tar.hpp"
#include <time.h>
#include <unistd.h>

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
    std::string tar_name = "/tmp/__dockerbuild_" + std::to_string(time(NULL)) + "_.tmp";
    if (access(tar_name.c_str(), F_OK) == 0) {
        remove(tar_name.c_str());
    }
    this->set_content_type("application/x-tar");
    std::string binary_payload;
    extensions::tar tar(tar_name, path);
    tar();
    tar.extract(binary_payload);
    this->set_binary_content(binary_payload);
    extensions::common_object obj = this->post_call<extensions::common_object>("/build?dockerfile=.%2FDockerfile"
                                                                               "&t="
                                                                               + tag);
    remove(tar_name.c_str());

    return obj;
}

}
}
