#ifndef _NAVAGRAHA_EXTENSION_SPECIAL_LIST_H
#define _NAVAGRAHA_EXTENSION_SPECIAL_LIST_H

#include "extensions/field.hpp"
#include "extensions/special_abstract_object.hpp"

namespace navagraha {
namespace extensions {

template <typename Special_Type>
class special_list : public special_abstract_object<special_list<Special_Type>, abstract_object_type_list> {
private:
    std::vector<Special_Type> _list;
public:
    std::vector<Special_Type> & values()
    {
        return this->_list;
    }

    special_list & serialize(std::ostringstream & str)
    {
        this->obj().list.clear();
        for (auto & item : this->_list) {
            this->obj().list.push_back(serializer<Special_Type>::to_abstract(item));
        }
        this->abstract_serialize(str);
        return *this;
    }

    special_list & deserialize(std::istringstream & str)
    {
        this->abstract_deserialize(str);
        this->_list.clear();
        for (auto & item : this->obj().list) {
            this->values().push_back(serializer<Special_Type>::to_special(item));
        }
        return *this;
    }

    static special_list deserialize(std::string & payload)
    {
        if (payload.length() == 0) {
            payload = "[]";
        }
        std::istringstream str(payload);
        special_list obj;

        obj.deserialize(str);
        return obj;
    }

    abstract_object to_abstract()
    {
        abstract_object ret;
        ret.type = abstract_object_type_list;
        for (auto & item : this->values()) {
            ret.list.push_back(serializer<Special_Type>::to_abstract(item));
        }
        return ret;
    }

    static special_list<Special_Type> to_special(abstract_object & obj)
    {
        special_list<Special_Type> ret;
        for (auto & item : obj.list) {
            ret.values().push_back(serializer<Special_Type>::to_special(item));
        }
        return ret;
    }
};

}
}

#endif
