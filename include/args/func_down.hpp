#ifndef _NAVAGRAHA_ARGS_FUNC_DOWN_H
#define _NAVAGRAHA_ARGS_FUNC_DOWN_H

#include <string>

namespace navagraha {
namespace args {

struct func_down {
    std::string namespace_;
    std::string name;
    bool stateful;
};

}
}

#endif
