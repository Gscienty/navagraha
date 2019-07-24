#include "cli/func_repo.hpp"
#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "docker_api/images.hpp"
#include <algorithm>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_FUNC_REPO_NAME[] = "repo";

void func_repo::bind(cli_arg::process_helper<func_repo> & helper)
{
    helper
        .add(this->name_arg);
}

bool func_repo::satisfy() const
{
    return this->name_arg.used();
}

int func_repo::execute()
{
    auto helper = http_client::curl_helper(config::get_instance().docker_sock)
        .unix_socket_build<docker_api::images>();

    helper.list()
        .response_switch()
        .response_case<200, extensions::special_list<dockerent::image>>(std::bind(&func_repo::images_for_each,
                                                                                  this,
                                                                                  std::placeholders::_1));

    return 0;
}

void func_repo::image_eachor(dockerent::image & image)
{
    if (image.labels.get().values().find(std::string("navafunc")) != image.labels.get().values().end()) {
        std::cout << image.repo_tags.get().values()[0] << std::endl;
    }
}

void func_repo::images_for_each(extensions::special_list<dockerent::image> & images)
{
    std::for_each(std::begin(images.values()),
                  std::end(images.values()),
                  std::bind(&func_repo::image_eachor, this, std::placeholders::_1));
}

}
}
