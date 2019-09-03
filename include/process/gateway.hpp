#ifndef _NAVAGRAHA_PROCESS_GATEWAY_H
#define _NAVAGRAHA_PROCESS_GATEWAY_H

#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "extensions/serializable.hpp"
#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include <string>

namespace navagraha {
namespace process {

struct gateway_set_arg {
    std::string namespace_;
    std::string policy;
    int replicas;
    std::string image;
};

struct gateway_get_arg {
    std::string namespace_;
};

struct gateway_remove_arg {
    std::string namespace_;
};

extern char GATEWAY_LIST_ITEM_NAMESPACE[];
extern char GATEWAY_LIST_ITEM_CLUSTER_IP[];
extern char GATEWAY_LIST_ITEM_IMAGE_TAG[];

class gateway_list_item : public extensions::serializable<gateway_list_item> {
public:
    extensions::field<std::string, GATEWAY_LIST_ITEM_NAMESPACE> namespace_;
    extensions::field<std::string, GATEWAY_LIST_ITEM_CLUSTER_IP> cluster_ip;
    extensions::field<std::string, GATEWAY_LIST_ITEM_IMAGE_TAG> image_tag;

    void bind(extensions::serializer_helper & helper);
};

extern char GATEWAY_REPO_LIST_ITEM_NAME[];
extern char GATEWAY_REPO_LIST_ITEM_VERSION[];

class gateway_repo_list_item : public extensions::serializable<gateway_repo_list_item> {
public:
    extensions::field<std::string, GATEWAY_REPO_LIST_ITEM_NAME> name;
    extensions::field<std::string, GATEWAY_REPO_LIST_ITEM_VERSION> version;

    void bind(extensions::serializer_helper & helper);
};

class gateway {
private:
    cli::config & config;

    void create_deployment(const gateway_set_arg & arg, http_client::curl_helper & helper);
    void create_service(const gateway_set_arg & arg, http_client::curl_helper & helper);
public:
    gateway(cli::config & cfg);

    std::string set(const gateway_set_arg & arg);

    extensions::special_list<gateway_list_item> get(const gateway_get_arg & arg);

    std::string remove(const gateway_remove_arg & arg);

    extensions::special_list<gateway_repo_list_item> repo();
};

}
}

#endif
