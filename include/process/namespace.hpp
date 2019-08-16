#ifndef _NAVAGRAHA_PROCESS_NAMESPACE_H
#define _NAVAGRAHA_PROCESS_NAMESPACE_H

#include "cli/config.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/namespace.hpp"
#include <string>

namespace navagraha {
namespace process {

extern char NAMESPACE_LIST_ITEM_NAME[];
extern char NAMESPACE_LIST_ITEM_STATUS[];

class namespace_list_item : public extensions::serializable<namespace_list_item> {
public:
    extensions::field<std::string, NAMESPACE_LIST_ITEM_NAME> name;
    extensions::field<std::string, NAMESPACE_LIST_ITEM_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

class namespace_ {
private:
    cli::config & config;

public:
    namespace_(cli::config & cfg);

    std::string add(std::string name);

    std::string remove(std::string name);

    extensions::special_list<namespace_list_item> list();
};

}
}

#endif
