#ifndef _NAVAGRAHA_EXTENSION_LIST_WRAPPER_H
#define _NAVAGRAHA_EXTENSION_LIST_WRAPPER_H

#include <list>
#include <functional>
#include <sstream>
#include "extensions/field.hpp"

namespace navagraha {
namespace extensions {

class list_wrapper {
public:
    std::list<std::function<void (std::ostringstream &)>> serializers;

    template <typename T_Field> void append(T_Field & field)
    {
        this->serializers.push_back(std::bind(&T_Field::serialize,
                                              field,
                                              std::placeholders::_1));
    }

    void append(std::string & field)
    {
        this->serializers.push_back(std::bind(&serializer<std::string>::serialize,
                                              field,
                                              std::placeholders::_1));
    }

    void append(int & field)
    {
        this->serializers.push_back(std::bind(&serializer<int>::serialize,
                                              field,
                                              std::placeholders::_1));
    }

    void append(bool & field)
    {
        this->serializers.push_back(std::bind(&serializer<bool>::serialize,
                                              field,
                                              std::placeholders::_1));
    }

    static void serialize(list_wrapper & obj, std::ostringstream & str);
};

template <typename T>
class special_list {
private:
    list_wrapper _wrapper;
public:
    void append(T & field)
    {
        this->_wrapper.append(field);
    }

    static void serialize(special_list<T> & obj, std::ostringstream & str)
    {
        list_wrapper::serialize(obj._wrapper, str);
    }
};

}
}

#endif
