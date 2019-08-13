#ifndef _NAVAGRAHA_ARGS_FUNC_UP_H
#define _NAVAGRAHA_ARGS_FUNC_UP_H

#include <string>

namespace navagraha {
namespace args {

struct func_up {
    std::string name;
    std::string policy;
    std::string image;
    std::string namespace_;
    bool stateful;
    bool update;
    int replicas;
};

}
}

#endif
