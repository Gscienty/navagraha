#include "extensions/abstract_object.hpp"
#include "extensions/serializer.hpp"
#include <algorithm>

namespace navagraha {
namespace extensions {

abstract_object::abstract_object(int val) : type(abstract_object_type_num)
{
    this->val.num = val;
}

abstract_object::abstract_object(bool val) : type(abstract_object_type_boolean)
{
    this->val.boolean = val;
}

abstract_object::abstract_object(const char * const val) : type(abstract_object_type_str)
{
    this->str = val;
}

abstract_object::abstract_object(std::string val) : type(abstract_object_type_str)
{
    this->str = val;
}

abstract_object::abstract_object() : type(abstract_object_type_obj)
{

}

abstract_object & abstract_object::serialize(std::ostringstream & str)
{
    bool first_field = true;
    switch (this->type) {
    case abstract_object_type_boolean:
        serializer<bool>::serialize(this->val.boolean, str);
        break;
    case abstract_object_type_str:
        serializer<std::string>::serialize(this->str, str);
        break;
    case abstract_object_type_num:
        serializer<int>::serialize(this->val.num, str);
        break;
    case abstract_object_type_obj:
        str.put('{');
        for (auto & item : this->obj) {
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
        for (auto & item : this->list) {
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

    return *this;
}

abstract_object & abstract_object::deserialize(std::istringstream & str)
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
        this->type = abstract_object_type_str;
        serializer<std::string>::deserialize(this->str, str);
        break;
    case 'a' ... 'z':
        this->type = abstract_object_type_boolean;
        serializer<bool>::deserialize(this->val.boolean, str);
        break;
    case '0' ... '9':
        this->type = abstract_object_type_num;
        serializer<int>::deserialize(this->val.num, str);
        break;
    case '{':
        this->type = abstract_object_type_obj;
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
            this->obj[key] = val;
        }
        str.get();
        break;
    case '[':
        this->type = abstract_object_type_list;
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
            this->list.push_back(val);
        }
        str.get();
    }

    return *this;
}
abstract_object abstract_object::to_abstract()
{
    return *this;
}

abstract_object abstract_object::to_special(abstract_object & obj)
{
    return obj;
}

}
}
