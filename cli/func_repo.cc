#include "cli/func_repo.hpp"
#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "docker_api/images.hpp"
#include "process/func.hpp"
#include <algorithm>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_FUNC_REPO_NAME[] = "repo";
char CLI_FUNC_REPO_FUNC_NAME[] = "--name";

void func_repo::bind(cli_arg::process_helper<func_repo> & helper)
{
    this->func_name_arg.require(this->name_arg);

    helper
        .add(this->name_arg)
        .add(this->func_name_arg);
}

bool func_repo::satisfy() const
{
    return this->name_arg.used();
}

int func_repo::execute()
{
    std::ostringstream oss;
    process::func(config::get_instance()).repo().serialize(oss);

    std::cout << oss.str() << std::endl;

    return 0;
}

}
}
