#ifndef _NAVAGRAHA_PROCESS_NAMESPACE_H
#define _NAVAGRAHA_PROCESS_NAMESPACE_H

#include "cli/config.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/namespace.hpp"
#include <string>

namespace navagraha {
namespace process {

class namespace_ {
private:
    cli::config & config;

public:
    namespace_(cli::config & cfg);

    std::string add(std::string name);

    std::string remove(std::string name);

    extensions::special_list<std::string> list();
};

}
}

#endif
