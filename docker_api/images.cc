#include "docker_api/images.hpp"
#include <time.h>
#include <unistd.h>
#include "extensions/tar.hpp"

namespace navagraha {
namespace docker_api {
images::images(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

images::images(CURL * curl)
    : http_client::client(curl, "http://localhost")
{

}

extensions::special_list<dockerent::image> images::list()
{
    return this->get_request("/images/json")
        .get<extensions::special_list<dockerent::image>>();
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
    extensions::common_object obj = this->post_request("/build?dockerfile=.%2FDockerfile"
                                                       "&t="
                                                       + tag)
        .get<extensions::common_object>();
    remove(tar_name.c_str());

    return obj;
}

}
}
