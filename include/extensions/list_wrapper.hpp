#ifndef _NAVAGRAHA_EXTENSION_LIST_WRAPPER_H
#define _NAVAGRAHA_EXTENSION_LIST_WRAPPER_H

#include <list>
#include <functional>
#include <sstream>
#include "extensions/field.hpp"

namespace navagraha {
namespace extensions {

class list_wrapper {
private:
    absobj_field_value _list;
public:
    list_wrapper();
    std::vector<absobj_field_value> & values();
    static void serialize(list_wrapper & obj, std::ostringstream & str);
    list_wrapper & serialize(std::ostringstream & str);
};

template <typename T>
class special_list {
private:
    list_wrapper _wrapper;
public:
    void append(T & field)
    {
        this->_wrapper.values().push_back(field);
    }

    static void serialize(special_list<T> & obj, std::ostringstream & str)
    {
        obj._wrapper.serialize(str);
    }
};

}
}

#endif
