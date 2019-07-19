#ifndef _NAVAGRAHA_EXTENSION_SERIALIZER_HELPER_H
#define _NAVAGRAHA_EXTENSION_SERIALIZER_HELPER_H

#include <list>
#include <functional>
#include <sstream>
#include <map>
#include "extensions/field.hpp"
#include "extensions/common_object.hpp"

namespace navagraha {
namespace extensions {

// 序列化/反序列化工具中工作类型
enum serializer_helper_type {
    serializer_helper_type_serialize,
    serializer_helper_type_deserialize,
    serializer_helper_type_to_abstract,
    serializer_helper_type_to_special
};

// 序列化/反序列化工具，包括序列化和反序列化两个字段结合
class serializer_helper {
private:
    serializer_helper_type  _type;
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> _serializers;
    std::map<std::string, std::function<void (std::istringstream &)>> _deserializers;
    common_object _obj;
public:
    // 当进行序列化或反序列化过程中，向序列化或反序列化字段集合中添加字段
    // 当进行抽象化或特例化过程中，将字段装填进common_object中，或将common_object中的值特例化到field中
    template <typename T_Field> serializer_helper & add(T_Field & field)
    {
        switch (this->_type) {
        case serializer_helper_type_serialize:
            if (field.omit() == false) {
                return *this;
            }
            this->_serializers.push_back(field_serializer(field));
            break;
        case serializer_helper_type_deserialize:
            this->_deserializers.insert(field_deserialize(field));
            break;
        case serializer_helper_type_to_abstract:
            if (field.omit() == false) {
                return *this;
            }
            this->_obj.values()[field.key] = field.to_abstract();
            break;
        case serializer_helper_type_to_special:
            std::string key = field.key;    
            auto obj_field_itr = this->_obj.values().find(key);
            if (obj_field_itr != this->_obj.values().end()) {
                field.to_special(obj_field_itr->second);
            }
            break;
        }
        return *this;
    }

    template <typename T_Func_Ptr, typename T_Obj_Ptr> abstract_object to_abstract(T_Func_Ptr func_ptr, T_Obj_Ptr obj_ptr)
    {
        this->_type = serializer_helper_type_to_abstract;
        (obj_ptr->*func_ptr)(*this);
        return this->_obj.to_abstract();
    }

    template <typename T_Func_Ptr, typename T_Obj_Ptr> T_Obj_Ptr serialize(T_Func_Ptr func_ptr, T_Obj_Ptr obj_ptr, std::ostringstream & str)
    {
        this->_type = serializer_helper_type_serialize;
        (obj_ptr->*func_ptr)(*this);
        str.put('{');
        fields_serialize(this->_serializers, str);
        str.put('}');

        return obj_ptr;
    }

    template <typename T_Func_Ptr, typename T_Obj_Ptr> T_Obj_Ptr deserialize(T_Func_Ptr func_ptr, T_Obj_Ptr obj_ptr, std::istringstream & str)
    {
        this->_type = serializer_helper_type_deserialize;
        (obj_ptr->*func_ptr)(*this);
        std::ostringstream key_str;
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

            auto deserialize_iter = this->_deserializers.find(key_str.str());
            if (deserialize_iter != this->_deserializers.end()) {
                deserialize_iter->second(str);
            }
            else {
                return obj_ptr;
            }
        }
        str.get();

        return obj_ptr;
    }

    template <typename T_Func_Ptr, typename T_Obj>
    T_Obj && to_special(T_Func_Ptr func_ptr, T_Obj && special_obj, abstract_object & obj)
    {
        this->_type = serializer_helper_type_to_special;
        this->_obj = obj;
        ((&special_obj)->*func_ptr)(*this);
        return std::move(special_obj);
    }
};

}
}

#endif
