#ifndef _NAVAGRAHA_KUBECTL_FIELD_H
#define _NAVAGRAHA_KUBECTL_FIELD_H

#include "extensions/omittable.hpp"
#include "extensions/static_constructable.hpp"
#include <functional>
#include <sstream>
#include <string.h>
#include <list>

namespace navagraha {
namespace extensions {

template <typename T_Type> struct serializer {
    static void serialize(T_Type & obj, std::ostringstream & str);
};

template <> struct serializer<std::string> {
    static void serialize(std::string & obj, std::ostringstream & str)
    {
        str.put('"');
        str.write(obj.data(), obj.size());
        str.put('"');
    }
};

template <> struct serializer<int> {
    static void serialize(int & obj, std::ostringstream & str)
    {
        std::string number = std::to_string(obj);
        str.write(number.data(), number.size());
    }
};

template <typename T_Type,
         const char * T_Name,
         typename T_Serializer = serializer<T_Type>>
class field : public omittable<T_Type> {
public:
    field<T_Type, T_Name, T_Serializer> & operator=(T_Type && obj)
    {
        this->omittable<T_Type>::operator=(obj);

        return *this;
    }

    void serialize(std::ostringstream & str)
    {
        str.put('"');
        str.write(T_Name, strlen(T_Name));
        str.put('"');
        str.put(':');
        T_Serializer::serialize(this->get(), str);
    }
};

template <typename T_Field>
inline
std::pair<bool, std::function<void (std::ostringstream &)>>
field_serializer(T_Field & field)
{
    return std::make_pair(field.omit(),
                          std::bind(&T_Field::serialize,
                                    &field,
                                    std::placeholders::_1));
}

void fields_serialize(std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> & serializers,
                      std::ostringstream & str);

}
}

#endif
