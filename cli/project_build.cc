#include "cli/project_build.hpp"
#include "cli/config.hpp"
#include "docker_api/images.hpp"
#include "dockerent/image_build_msg.hpp"
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_FUNC_BUILD_BUILD[] = "build";
char CLI_FUNC_BUILD_PATH[] = "--path";

void project_build::bind(cli_arg::process_helper<project_build> & helper)
{
    this->path_arg.require(this->build_arg);

    helper
        .add(this->build_arg)
        .add(this->path_arg);
}

bool project_build::satisfy() const
{
    return this->build_arg.used();
}

int project_build::execute()
{
    auto helper = http_client::curl_helper(config::get_instance().docker_sock)
        .unix_socket_build<docker_api::images>();
    std::string path = this->path_arg.used() ? this->path_arg[0] : ".";
    helper.create(path, this->build_arg[0], std::bind(&project_build::received_callback,
                                                      this,
                                                      std::placeholders::_1));
    return 0;
}

void project_build::received_callback(std::string & msg)
{
    dockerent::image_build_msg msg_obj = dockerent::image_build_msg::deserialize(msg);

    bool tc = false;
    for (char c : msg_obj.stream.get()) {
        if (tc) {
            switch (c) {
            case 'n':
                std::cout << std::endl;
                break;
            case '\\':
                std::cout << '\\';
            }
            tc = false;
        }
        else if (c != '\\') {
            std::cout << c;
        }
        else {
            tc = true;
        }
    }
}

}
}
