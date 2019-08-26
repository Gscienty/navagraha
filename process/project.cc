#include "process/project.hpp"
#include "git/repo_init.hpp"
#include "http_client/curl_helper.hpp"
#include "docker_api/images.hpp"

namespace navagraha {
namespace process {

project::project(cli::config & cfg)
    : config(cfg)
{

}

std::string project::init(project_init_arg & arg)
{
    navagraha::git::repo_init git_repo(arg.path,
                                       arg.use_local
                                       ? arg.local_template_path
                                       : "https://github.com/Gscienty/navagraha.git",
                                       arg.use_local,
                                       "template/" + arg.type);

    git_repo.init();
    git_repo.fetch_template();

    return "";
}

std::string project::build(project_build_arg & arg)
{
    auto helper = http_client::curl_helper(this->config.docker_sock)
        .unix_socket_build<docker_api::images>();
    helper.create(arg.path,
                  arg.name + ":" + arg.version,
                  bool(arg.callback)
                  ? arg.callback
                  : std::bind(&project::build_callback, this, std::placeholders::_1));
    helper.delete_builder_cache();

        return "";
}

std::string project::remove(project_remove_arg & arg)
{
    http_client::curl_helper(this->config.docker_sock)
        .unix_socket_build<docker_api::images>()
        .remove(arg.name + ":" + arg.version);

    return "";
}

void project::build_callback(std::string & val)
{
    std::cout << val << std::endl;
}

}
}
