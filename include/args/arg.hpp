#ifndef _NAGAGRAHA_ARG_ARG_H
#define _NAGAGRAHA_ARG_ARG_H

#include "args/param.hpp"
#include <string>
#include <vector>
#include <map>
#include <set>

namespace navagraha {
namespace arg {

class arg {
private:
    const arg * _prerequired;
    const std::string _name;
    param _params;
    bool _used;
    std::map<std::string, size_t> _indices;

public:
    arg(const arg * prerequired, const std::string name,
        const size_t params_count);

    arg(const std::string name, const size_t params_count);

    bool append_param(const char * param);

    size_t remain_param_count() const;

    std::vector<std::string> & values();

    std::string value(std::string key);

    bool set_index(std::string key, size_t index);

    bool hit();

    bool & used();

    arg * pointer();
};

}
}

#endif
