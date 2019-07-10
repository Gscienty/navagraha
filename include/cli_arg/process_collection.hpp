#ifndef _NAVAGRAHA_CLI_ARG_PROCESS_COLLECTION_H
#define _NAVAGRAHA_CLI_ARG_PROCESS_COLLECTION_H

#include "cli_arg/process_helper.hpp"
#include <functional>

namespace navagraha {
namespace cli_arg {

class process_collection {
private:
    bool hited;
    int ret;
    int argc;
    char ** argv;
    std::function<int ()> default_;
public:
    process_collection(int argc, char ** argv);

    template <typename T_Process> process_collection & add(T_Process process)
    {
        if (hited == true) {
            return *this;
        }
        process_helper<T_Process> helper(process);

        this->hited = helper.bind(this->argc, this->argv)();
        this->ret = helper.result();

        return *this;
    }

    template <typename T_Process> process_collection & default_process(T_Process process)
    {
        if (hited == true) {
            return *this;
        }
        process_helper<T_Process> helper(process);

        helper.bind(this->argc, this->argv)();
        this->ret = helper.result();

        return *this;
    }

    int result();
};

}
}

#endif
