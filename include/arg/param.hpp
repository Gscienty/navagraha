#ifndef _NAVAGRAHA_ARG_PARAM_H
#define _NAVAGRAHA_ARG_PARAM_H

#include <vector>
#include <string>

namespace navagraha {
namespace arg {

class param {
private:
    const size_t _params_count;
    size_t _used_count;
    std::vector<std::string> _params;

public:
    param(const size_t params_count);

    size_t required_count() const;

    size_t used_count() const;

    bool append(const char * param);

    std::vector<std::string> & value();
};

}
}

#endif
