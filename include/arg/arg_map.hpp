#ifndef _NAVAGRAHA_ARG_ARG_MAP_H
#define _NAVAGRAHA_ARG_ARG_MAP_H

#include "arg/arg.hpp"
#include <map>
#include <string>
#include <list>
#include <memory>

namespace navagraha {
namespace arg {

class arg_map {
private:
    static std::map<std::string,
        std::list<std::shared_ptr<arg>>> _arg_map;
    std::shared_ptr<arg> _ptr;

    void _put_arg_map(const char * arg_name);
public:
    arg_map(std::shared_ptr<arg> & prerequired, const char * arg_name,
            size_t params_count);
    arg_map(const char * arg_name, size_t params_count);

    std::shared_ptr<arg> & ptr();
};

}
}

#endif
