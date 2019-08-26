#ifndef _NAVAGRAHA_PROCESS_PROJECT_H
#define _NAVAGRAHA_PROCESS_PROJECT_H

#include "cli/config.hpp"
#include <functional>
#include <string>

namespace navagraha {
namespace process {

struct project_init_arg {
    std::string path;
    std::string type;
    bool use_local;
    std::string local_template_path;
};

struct project_build_arg {
    std::string name;
    std::string version;
    std::string path;
    std::function<void (std::string &)> callback;
};

struct project_remove_arg {
    std::string name;
    std::string version;
};

class project {
private:
    cli::config & config;

    void build_callback(std::string & msg);
public:
    project(cli::config & cfg);

    std::string init(project_init_arg & arg);

    std::string build(project_build_arg & arg);

    std::string remove(project_remove_arg & arg);
};

}
}

#endif
