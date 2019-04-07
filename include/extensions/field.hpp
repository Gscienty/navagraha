#ifndef _NAVAGRAHA_EXTENSION_FIELD_H
#define _NAVAGRAHA_EXTENSION_FIELD_H

#include "extensions/omittable.hpp"
#include "extensions/static_constructable.hpp"
#include <functional>
#include <sstream>
#include <string.h>
#include <list>

namespace navagraha {
namespace extensions {

template <typename T_Type> struct serializer {
    static void serialize(T_Type & obj, std::ostringstream & str)
    {
        T_Type::serialize(obj, str);
    }

    static void deserialize(T_Type & obj, std::istringstream & str)
    {
        T_Type::deserialize(obj, str);
    }
};

template <> struct serializer<std::string> {
    static void serialize(std::string & obj, std::ostringstream & str)
    {
        str.put('"');
        str.write(obj.data(), obj.size());
        str.put('"');
    }

    static void deserialize(std::string & obj, std::istringstream & str)
    {
        char c;
        while (c = str.get(), c != '"');
        for (c = str.get(); c != '"' || (*obj.rbegin() == '\\'); c = str.get()) {
            obj.push_back(c);
        }
        str.get();
    }
};

template <> struct serializer<int> {
    static void serialize(int & obj, std::ostringstream & str)
    {
        std::string number = std::to_string(obj);
        str.write(number.data(), number.size());
    }

    static void deserialize(int & obj, std::istringstream & str)
    {
        std::stringstream num_str;
        while (str.peek() < '0' || '9' < str.peek()) {
            str.get();
        }
        while ('0' <= str.peek() && str.peek() <= '9') {
            num_str.put(str.get());
        }
        obj = std::stoi(num_str.str());
    }
};

template <> struct serializer<bool> {
    static void serialize(bool & obj, std::ostringstream & str)
    {
        std::string boolean(obj ? "true" : "false");
        str.write(boolean.data(), boolean.size());
    }

    static void deserialize(bool & obj, std::istringstream & str)
    {
        std::stringstream bool_str;
        while (str.peek() < 'a' || 'z' < str.peek()) {
            str.get();
        }
        while ('a' <= str.peek() && str.peek() <= 'z') {
            bool_str.put(str.get());
        }
        std::string bool_ = bool_str.str();

        if (bool_.compare("true")) {
            obj = true;
        }
        else if (bool_.compare("false")) {
            obj = false;
        }
    }
};

template <typename T_Type,
         const char * T_Name,
         typename T_Serializer = serializer<T_Type>>
class field : public omittable<T_Type> {
public:
    const char * const field_name = T_Name;

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
        T_Serializer::serialize(this->omittable<T_Type>::get(), str);
    }

    void deserialize(std::istringstream & str)
    {
        while (str.peek() != ':') {
            str.get();
        }
        T_Serializer::deserialize(this->omittable<T_Type>::get(), str);
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
