#ifndef _NAVAGRAHA_EXTENSION_FIELD_H
#define _NAVAGRAHA_EXTENSION_FIELD_H

#include "extensions/omittable.hpp"
#include "extensions/static_constructable.hpp"
#include <functional>
#include <sstream>
#include <string.h>
#include <list>
#include <string>
#include <map>
#include <vector>

#include <iostream>

namespace navagraha {
namespace extensions {

enum absobj_field_type {
    absobj_field_type_obj,
    absobj_field_type_list,
    absobj_field_type_str,
    absobj_field_type_num,
    absobj_field_type_boolean
};

struct absobj_field_value {
    absobj_field_type type;
    union {
        int num;
        bool boolean;
    } val;
    std::string str;
    std::map<std::string, absobj_field_value> obj;
    std::vector<absobj_field_value> list;

    absobj_field_value();
    absobj_field_value(int val);
    absobj_field_value(bool val);
    absobj_field_value(const char * const val);
    absobj_field_value(std::string val);

    static void serialize(absobj_field_value & obj, std::ostringstream & str);

    static void deserialize(absobj_field_value & obj, std::istringstream & str);

    absobj_field_value & self_serialize(std::ostringstream & str);

    absobj_field_value & self_deserialize(std::istringstream & str);
};

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

        if (bool_.compare("true") == 0) {
            obj = true;
        }
        else if (bool_.compare("false") == 0) {
            obj = false;
        }
    }
};

template <> struct serializer<absobj_field_value> {
    static void serialize(absobj_field_value & obj, std::ostringstream & str)
    {
        bool first_field = true;
        switch (obj.type) {
        case absobj_field_type_boolean:
            serializer<bool>::serialize(obj.val.boolean, str);
            break;
        case absobj_field_type_str:
            serializer<std::string>::serialize(obj.str, str);
            break;
        case absobj_field_type_num:
            serializer<int>::serialize(obj.val.num, str);
            break;
        case absobj_field_type_obj:
            str.put('{');
            for (auto & item : obj.obj) {
                if (first_field) {
                    first_field = false;
                }
                else {
                    str.put(',');
                }
                str.put('"');
                str.write(item.first.c_str(), item.first.size());
                str.put('"');
                str.put(':');
                serializer<absobj_field_value>::serialize(item.second, str);
            }
            str.put('}');
            break;
        case absobj_field_type_list:
            str.put('[');
            for (auto & item : obj.list) {
                if (first_field) {
                    first_field = false;
                }
                else {
                    str.put(',');
                }
                serializer<absobj_field_value>::serialize(item, str);
            }
            str.put(']');
        }
    }

    static void deserialize(absobj_field_value & obj, std::istringstream & str)
    {
        std::ostringstream key_str;

        while (str.peek() != '"'
               && (str.peek() < 'a' || 'z' < str.peek())
               && str.peek() != '{'
               && (str.peek() < '0' || '9' < str.peek())) {
            str.get();
        }

        switch (str.peek()) {
        case '"':
            obj.type = absobj_field_type_str;
            serializer<std::string>::deserialize(obj.str, str);
            break;
        case 'a' ... 'z':
            obj.type = absobj_field_type_boolean;
            serializer<bool>::deserialize(obj.val.boolean, str);
            break;
        case '0' ... '9':
            obj.type = absobj_field_type_num;
            serializer<int>::deserialize(obj.val.num, str);
            break;
        case '{':
            obj.type = absobj_field_type_obj;
            while (str.peek() != '}') {
                key_str.str("");
                while (str.peek() != '"' && str.peek() != '}') {
                    str.get();
                }
                if (str.peek() == '}') {
                    break;
                }
                str.get();
                while(str.peek() != '"') {
                    key_str.put(str.get());
                }
                while (str.peek() != ':') {
                    str.get();
                }
                std::string key = key_str.str();
                absobj_field_value val;
                serializer<absobj_field_value>::deserialize(val, str);
                obj.obj[key] = val;
            }
            break;
        case '[':
            obj.type = absobj_field_type_list;
            while (str.peek() != ']') {
                absobj_field_value val;
                serializer<absobj_field_value>::deserialize(val, str);
                obj.list.push_back(val);
            }
        }
    }
};

template <typename T_Type,
         const char * T_Name,
         typename T_Serializer = serializer<T_Type>>
class field : public omittable<T_Type> {
public:
    const char * const key = T_Name;

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

template <typename T_Field>
inline
std::pair<std::string, std::function<void (std::istringstream &)>>
field_deserialize(T_Field & field)
{
    return std::make_pair(std::string(field.key),
                          std::bind(&T_Field::deserialize,
                                    &field,
                                    std::placeholders::_1));
}

void fields_serialize(std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> & serializers,
                      std::ostringstream & str);

}
}

#endif
