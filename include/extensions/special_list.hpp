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
            this->obj.list.push_back(item.to_abstract());
        }
        this->special_abstract_object<Special_Type, abstract_object_type_list>::serialize(str);
    }

    special_list * deserialize(std::istringstream & str)
    {
        this->special_abstract_object<Special_Type, abstract_object_type_list>::deserialize(str);

        // TODO abstract_object to special_object
    }


    abstract_object to_abstract()
    {
        this->obj().list.clear();
        for (auto & item : this->_list) {
            this->obj.list.push_back(item.to_abstract());
        }

        return this->obj();
    }
};

}
}

#endif
