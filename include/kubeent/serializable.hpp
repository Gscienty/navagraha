#ifndef _NAVAGRAHA_KUBEENT_SERIALIZABLE_H
#define _NAVAGRAHA_KUBEENT_SERIALIZABLE_H

#include "extensions/serializer_helper.hpp"
#include "extensions/field.hpp"
#include <sstream>

namespace navagraha {
namespace kubeent {

template <typename T_Obj>
class serializable {
public:
    T_Obj & serialize(std::ostringstream & str)
    {
        return *extensions::serializer_helper()
            .serialize(&T_Obj::bind, reinterpret_cast<T_Obj *>(this), str);
    }

    T_Obj & deserialize(std::istringstream & str)
    {
        return *extensions::serializer_helper()
            .deserialize(&T_Obj::bind, reinterpret_cast<T_Obj *>(this), str);
    }

    static T_Obj deserialize(std::string & payload)
    {
        std::istringstream str(payload);
        T_Obj obj;

        obj.deserialize(str);
        return obj;
    }

    extensions::abstract_object to_abstract()
    {
        return extensions::serializer_helper()
            .to_abstract(&T_Obj::bind, reinterpret_cast<T_Obj *>(this));
    }

    static T_Obj to_special(extensions::abstract_object & obj)
    {
        return extensions::serializer_helper()
            .to_special(&T_Obj::bind, T_Obj(), obj);
    }
};

}
}

#endif
