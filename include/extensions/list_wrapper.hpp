#ifndef _NAVAGRAHA_EXTENSION_LIST_WRAPPER_H
#define _NAVAGRAHA_EXTENSION_LIST_WRAPPER_H

#include <list>
#include <functional>
#include <sstream>

namespace navagraha {
namespace extensions {

class list_wrapper {

public:
    std::list<std::function<void (std::ostringstream &)>> serializers;

    template<typename T_Field> void append(T_Field & field)
    {
        this->serializers.push_back(std::bind(&T_Field::serialize,
                                              field,
                                              std::placeholders::_1));
    }

    static void serialize(list_wrapper & obj, std::ostringstream & str);
};

}
}

#endif
