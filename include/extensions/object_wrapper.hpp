#ifndef _NAVAGRAHA_EXTENSION_OBJECT_WRAPPER_H
#define _NAVAGRAHA_EXTENSION_OBJECT_WRAPPER_H

#include <functional>
#include <sstream>

namespace navagraha {
namespace extensions {

class object_wrapper {
public:
    std::function<void (std::ostringstream &)> serializer;

    static void serialize(object_wrapper & obj, std::ostringstream & str);

    void serialize(std::ostringstream & str);

    template <typename T_Field> object_wrapper & operator= (T_Field & field)
    {
        this->serializer = std::bind(&T_Field::serialize,
                                     field,
                                     std::placeholders::_1);
    }
};

}
}

#endif
