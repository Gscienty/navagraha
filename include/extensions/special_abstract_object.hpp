#ifndef _NAVAGRAHA_EXTENSION_SPECIAL_ABSTRACT_OBJECT_H
#define _NAVAGRAHA_EXTENSION_SPECIAL_ABSTRACT_OBJECT_H

#include "extensions/field.hpp"

namespace navagraha {
namespace extensions {

template<typename T, abstract_object_type Abstract_Object_Type>
class special_abstract_object {
private:
    abstract_object _obj;

protected:
    abstract_object & obj()
    {
        return this->_obj;
    }

public:
    special_abstract_object()
    {
        this->_obj.type = Abstract_Object_Type;
    }

    special_abstract_object & abstract_serialize(std::ostringstream & str)
    {
        this->_obj.serialize(str);
        return *this;
    }

    special_abstract_object & abstract_deserialize(std::istringstream & str)
    {
        this->_obj.deserialize(str);
        return *this;
    }

    abstract_object to_abstract()
    {
        return this->_obj;
    }
};

}
}


#endif
