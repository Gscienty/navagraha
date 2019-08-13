#ifndef _NAVAGRAHA_PROCESS_FUNC_H
#define _NAVAGRAHA_PROCESS_FUNC_H

#include "cli/config.hpp"
#include "args/func_up.hpp"
#include "args/func_down.hpp"
#include "http_client/curl_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "extensions/field.hpp"
#include "dockerent/image.hpp"

namespace navagraha {
namespace process {

extern char FUNC_REPO_ITEM_NAME[];
extern char FUNC_REPO_ITEM_VERSIONS[];

class func_repo_item : public extensions::serializable<func_repo_item> {
public:
    extensions::field<std::string, FUNC_REPO_ITEM_NAME> name;
    extensions::field<extensions::special_list<std::string>, FUNC_REPO_ITEM_VERSIONS> versions;

    void bind(extensions::serializer_helper & helper);
};

class func {
private:
    cli::config & config;

    void func_up_create_deployment(http_client::curl_helper & helper,
                                   const args::func_up & func_up);
    void func_up_create_service(http_client::curl_helper & helper,
                                const args::func_up & func_up);
    void func_up_create_statefulset(http_client::curl_helper & helper,
                                    const args::func_up & func_up);
    void func_repo_image_filter(std::map<std::string, std::list<std::string>> & stored,
                                navagraha::dockerent::image & image);

public:
    func(cli::config & cfg);

    std::string up(const args::func_up & func_up);

    std::string down(const args::func_down & func_down);

    extensions::special_list<func_repo_item> repo();
};

}
}

#endif
