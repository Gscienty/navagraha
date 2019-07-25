#include "cli/func_repo.hpp"
#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "docker_api/images.hpp"
#include <algorithm>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_FUNC_REPO_NAME[] = "repo";
char CLI_FUNC_REPO_FUNC_NAME[] = "--name";

void func_repo::bind(cli_arg::process_helper<func_repo> & helper)
{
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
    auto helper = http_client::curl_helper(config::get_instance().docker_sock)
        .unix_socket_build<docker_api::images>();

    helper.list()
        .response_switch()
        .response_case<200, extensions::special_list<dockerent::image>>(std::bind(&func_repo::images_for_each,
                                                                                  this,
                                                                                  std::placeholders::_1));

    return 0;
}

void func_repo::image_eachor(std::map<std::string, std::list<std::string>> &store, dockerent::image & image)
{
    if (image.labels.get().values().find(std::string("navafunc")) != image.labels.get().values().end()) {
        std::string fullname = image.repo_tags.get().values().front();
        std::string::iterator tag_spliter = std::find(std::begin(fullname), std::end(fullname), ':');

        if (tag_spliter == std::end(fullname)) {
            if (store.find(fullname) == std::end(store)) {
                if (this->name_arg.used() && fullname.compare(this->name_arg[0]) != 0) {
                    return;
                }
                store.insert(std::make_pair(fullname, std::list<std::string>()));
            }
        }
        else {
            std::string tag_name(std::begin(fullname), tag_spliter);
            if (this->name_arg.used() && tag_name.compare(this->name_arg[0]) != 0) {
                return;
            }
            tag_spliter++;
            std::string version(tag_spliter, std::end(fullname));
            if (store.find(tag_name) == std::end(store)) {
                store.insert(std::make_pair(tag_name, std::list<std::string>()));
            }
            store[tag_name].push_back(version);
        }
    }
}

void func_repo::images_for_each(extensions::special_list<dockerent::image> & images)
{
    std::map<std::string, std::list<std::string>> store;
    for (auto image : images.values()) {
        this->image_eachor(store, image);
    }
    for (auto pair : store) {
        std::cout << pair.first << '\t';

        for (auto version : pair.second) {
            std::cout << version << ' ';
        }
        std::cout << std::endl;
    }
}

}
}
