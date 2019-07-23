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

http_client::http_response images::list()
{
    return this->get_request("/images/json");
}

http_client::http_response images::create(std::string path, std::string tag, std::function<void (std::string &)> cb)
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
    remove(tar_name.c_str());
    this->set_binary_content(binary_payload);
    this->set_receive_cb(cb);
    return this->post_request("/build?dockerfile=.%2FDockerfile"
                              "&t="
                              + tag);
}

}
}
