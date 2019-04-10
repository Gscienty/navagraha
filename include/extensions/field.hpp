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

namespace navagraha {
namespace extensions {

enum abstract_object_type {
    abstract_object_type_obj,
    abstract_object_type_list,
    abstract_object_type_str,
    abstract_object_type_num,
    abstract_object_type_boolean
};

struct abstract_object {
    abstract_object_type type;
    union {
        int num;
        bool boolean;
    } val;
    std::string str;
    std::map<std::string, abstract_object> obj;
    std::vector<abstract_object> list;

    abstract_object();
    abstract_object(int val);
    abstract_object(bool val);
    abstract_object(const char * const val);
    abstract_object(std::string val);

    abstract_object & serialize(std::ostringstream & str);
    abstract_object & deserialize(std::istringstream & str);
    abstract_object to_abstract();
};

template <typename T_Type> struct serializer {
    static void serialize(T_Type & obj, std::ostringstream & str)
    {
        obj.serialize(str);
    }

    static void deserialize(T_Type & obj, std::istringstream & str)
    {
        obj.deserialize(str);
    }

    static abstract_object to_abstract(T_Type & obj)
    {
        return obj.to_abstract();
    }

    static T_Type to_special(abstract_object & obj)
    {
        return T_Type::to_special(obj);
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

    static abstract_object to_abstract(std::string & obj)
    {
        return abstract_object(obj);
    }

    static std::string to_special(abstract_object & obj)
    {
        if (obj.type != abstract_object_type_str) {
            return std::string();
        }
        return obj.str;
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

    static abstract_object to_abstract(int & obj)
    {
        return abstract_object(obj);
    }

    static int to_special(abstract_object & obj)
    {
        if (obj.type != abstract_object_type_num) {
            return 0;
        }
        return obj.val.num;
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

    static abstract_object to_abstract(bool & obj)
    {
        return abstract_object(obj);
    }

    static bool to_special(abstract_object & obj)
    {
        if (obj.type != abstract_object_type_boolean) {
            return false;
        }
        return obj.val.boolean;
    }
};

template <> struct serializer<abstract_object> {
    static void serialize(abstract_object & obj, std::ostringstream & str)
    {
        bool first_field = true;
        switch (obj.type) {
        case abstract_object_type_boolean:
            serializer<bool>::serialize(obj.val.boolean, str);
            break;
        case abstract_object_type_str:
            serializer<std::string>::serialize(obj.str, str);
            break;
        case abstract_object_type_num:
            serializer<int>::serialize(obj.val.num, str);
            break;
        case abstract_object_type_obj:
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
                serializer<abstract_object>::serialize(item.second, str);
            }
            str.put('}');
            break;
        case abstract_object_type_list:
            str.put('[');
            for (auto & item : obj.list) {
                if (first_field) {
                    first_field = false;
                }
                else {
                    str.put(',');
                }
                serializer<abstract_object>::serialize(item, str);
            }
            str.put(']');
        }
    }

    static void deserialize(abstract_object & obj, std::istringstream & str)
    {
        std::ostringstream key_str;

        while (str.peek() != '"'
               && (str.peek() < 'a' || 'z' < str.peek())
               && str.peek() != '{'
               && str.peek() != '['
               && (str.peek() < '0' || '9' < str.peek())) {
            str.get();
        }

        switch (str.peek()) {
        case '"':
            obj.type = abstract_object_type_str;
            serializer<std::string>::deserialize(obj.str, str);
            break;
        case 'a' ... 'z':
            obj.type = abstract_object_type_boolean;
            serializer<bool>::deserialize(obj.val.boolean, str);
            break;
        case '0' ... '9':
            obj.type = abstract_object_type_num;
            serializer<int>::deserialize(obj.val.num, str);
            break;
        case '{':
            obj.type = abstract_object_type_obj;
            str.get();
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
                abstract_object val;
                serializer<abstract_object>::deserialize(val, str);
                obj.obj[key] = val;
            }
            break;
        case '[':
            obj.type = abstract_object_type_list;
            str.get();
            while (str.peek() != ']') {
                while (str.peek() != '"'
                       && (str.peek() < 'a' || 'z' < str.peek())
                       && str.peek() != '{'
                       && str.peek() != '['
                       && (str.peek() < '0' || '9' < str.peek())
                       && str.peek() != ']') {
                    str.get();
                }
                if (str.peek() == ']') {
                    break;
                }
                abstract_object val;
                serializer<abstract_object>::deserialize(val, str);
                obj.list.push_back(val);
            }
        }
    }

    static abstract_object to_abstract(abstract_object & obj)
    {
        return obj;
    }

    static abstract_object to_special(abstract_object & obj)
    {
        return obj;
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
        T_Serializer::serialize(this->get(), str);
    }

    void deserialize(std::istringstream & str)
    {
        while (str.peek() != ':') {
            str.get();
        }
        T_Serializer::deserialize(this->get(), str);
    }

    void to_special(abstract_object & obj)
    {
        T_Type special_val = T_Serializer::to_special(obj);
        this->omittable<T_Type>::get() = special_val;
    }

    abstract_object to_abstract()
    {
        return serializer<T_Type>::to_abstract(this->get());
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
