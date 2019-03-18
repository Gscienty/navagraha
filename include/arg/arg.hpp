#ifndef _NAGAGRAHA_ARG_ARG_H
#define _NAGAGRAHA_ARG_ARG_H

#include "arg/param.hpp"
#include <string>
#include <vector>
#include <boost/function.hpp>
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
    boost::function<bool (const arg &)> _satisfy;
    std::map<std::string, size_t> _indices;
    std::set<std::string> _other_name;

public:
    arg(const arg * prerequired, const std::string name,
        const size_t params_count);

    arg(const std::string name, const size_t params_count);

    bool append_param(const char * param);

    size_t remain_param_count() const;

    std::vector<std::string> & value();

    std::string value(std::string key);

    bool set_index(std::string key, size_t index);

    void set_satisfy(boost::function<bool (const arg &)> satisfy);

    bool satisfy();

    void add_other_name(std::string name);

    bool hit(const char * arg_name);

    void used();

    arg * pointer();
};

}
}

#endif
