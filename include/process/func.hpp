#ifndef _NAVAGRAHA_PROCESS_FUNC_H
#define _NAVAGRAHA_PROCESS_FUNC_H

#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "extensions/field.hpp"
#include "dockerent/image.hpp"
#include "kubeent/service_list.hpp"

namespace navagraha {
namespace process {

struct func_down_arg {
    std::string namespace_;
    std::string name;
    bool stateful;
};

struct func_up_arg {
    std::string name;
    std::string policy;
    std::string image;
    std::string namespace_;
    bool stateful;
    bool update;
    int replicas;
};

struct func_list_arg {
    std::string namespace_;
};

struct func_pod_list_arg {
    std::string namespace_;
    std::string name;
};

struct func_autoscaling_arg {
    std::string name;
    std::string namespace_;
    int cpu;
    int min;
    int max;
};

struct func_autoscaling_list_arg {
    std::string name;
    std::string namespace_;
};

struct func_repo_remove_arg {
    std::string name;
    std::string version;
};

extern char FUNC_REPO_ITEM_NAME[];
extern char FUNC_REPO_ITEM_VERSIONS[];

class func_repo_item : public extensions::serializable<func_repo_item> {
public:
    extensions::field<std::string, FUNC_REPO_ITEM_NAME> name;
    extensions::field<extensions::special_list<std::string>, FUNC_REPO_ITEM_VERSIONS> versions;

    void bind(extensions::serializer_helper & helper);
};

extern char FUNC_LIST_ITEM_NAMESPACE[];
extern char FUNC_LIST_ITEM_NAME[];
extern char FUNC_LIST_ITEM_STATEFUL[];
extern char FUNC_LIST_ITEM_IMAGE_TAG[];
extern char FUNC_LIST_ITEM_REPLICAS[];
extern char FUNC_LIST_ITEM_AVAILABLE[];
extern char FUNC_LIST_ITEM_UNAVAILABLE[];

class func_list_item : public extensions::serializable<func_list_item> {
public:
    extensions::field<std::string, FUNC_LIST_ITEM_NAMESPACE> namespace_;
    extensions::field<std::string, FUNC_LIST_ITEM_NAME> name;
    extensions::field<bool, FUNC_LIST_ITEM_STATEFUL> stateful;
    extensions::field<std::string, FUNC_LIST_ITEM_IMAGE_TAG> image_tag;
    extensions::field<int, FUNC_LIST_ITEM_REPLICAS> replicas;
    extensions::field<int, FUNC_LIST_ITEM_AVAILABLE> available;
    extensions::field<int, FUNC_LIST_ITEM_UNAVAILABLE> unavailable;

    void bind(extensions::serializer_helper & helper);
};

extern char FUNC_POD_LIST_ITEM_NAMESPACE[];
extern char FUNC_POD_LIST_ITEM_NAME[];
extern char FUNC_POD_LIST_ITEM_STATUS[];
extern char FUNC_POD_LIST_ITEM_IMAGE[];
extern char FUNC_POD_LIST_ITEM_POLICY[];
extern char FUNC_POD_LIST_ITEM_NODE[];

class func_pod_list_item : public extensions::serializable<func_pod_list_item> {
public:
    extensions::field<std::string, FUNC_POD_LIST_ITEM_NAMESPACE> namespace_;
    extensions::field<std::string, FUNC_POD_LIST_ITEM_NAME> name;
    extensions::field<std::string, FUNC_POD_LIST_ITEM_STATUS> status;
    extensions::field<std::string, FUNC_POD_LIST_ITEM_IMAGE> image;
    extensions::field<std::string, FUNC_POD_LIST_ITEM_POLICY> policy;
    extensions::field<std::string, FUNC_POD_LIST_ITEM_NODE> node;

    void bind(extensions::serializer_helper & helper);
};

extern char FUNC_AUTOSCALING_LIST_ITEM_NAME[];
extern char FUNC_AUTOSCALING_LIST_ITEM_CPU[];
extern char FUNC_AUTOSCALING_LIST_ITEM_MIN_REPLICAS[];
extern char FUNC_AUTOSCALING_LIST_ITEM_MAX_REPLICAS[];
extern char FUNC_AUTOSCALING_LIST_ITEM_TARGET[];

class func_autoscaling_list_item : public extensions::serializable<func_autoscaling_list_item> {
public:
    extensions::field<std::string, FUNC_AUTOSCALING_LIST_ITEM_NAME> name;
    extensions::field<int, FUNC_AUTOSCALING_LIST_ITEM_CPU> cpu;
    extensions::field<int, FUNC_AUTOSCALING_LIST_ITEM_MIN_REPLICAS> min;
    extensions::field<int, FUNC_AUTOSCALING_LIST_ITEM_MAX_REPLICAS> max;
    extensions::field<std::string, FUNC_AUTOSCALING_LIST_ITEM_TARGET> target;

    void bind(extensions::serializer_helper & helper);
};

class func {
private:
    cli::config & config;

    void func_up_create_deployment(http_client::curl_helper & helper,
                                   const func_up_arg & func_up);
    void func_up_create_service(http_client::curl_helper & helper,
                                const func_up_arg & func_up);
    void func_up_create_statefulset(http_client::curl_helper & helper,
                                    const func_up_arg & func_up);
    void func_repo_image_filter(std::map<std::string, std::list<std::string>> & stored,
                                dockerent::image & image);
public:
    func(cli::config & cfg);

    std::string up(const func_up_arg & func_up);

    std::string down(const func_down_arg & func_down);

    extensions::special_list<func_repo_item> repo();

    int repoRemove(const std::string name);

    extensions::special_list<func_list_item> list(const func_list_arg & arg);

    extensions::special_list<func_pod_list_item> list_pod(const func_pod_list_arg & arg);

    std::string autoscaling(const func_autoscaling_arg & arg);

    extensions::special_list<func_autoscaling_list_item> list_autoscaling(const func_autoscaling_list_arg & arg);
};

}
}

#endif
