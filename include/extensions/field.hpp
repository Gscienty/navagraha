#ifndef _NAVAGRAHA_EXTENSION_FIELD_H
#define _NAVAGRAHA_EXTENSION_FIELD_H

/**
 *
 * 该文件主要是处理实体类各个字段的序列化与反序列化功能。
 * 每个消息实体中的字段，可以归纳包括五类字段类型：
 * 1. 对象类型
 * 2. 列表类型
 * 3. 字符串类型
 * 4. 数字类型
 * 5. 布尔类型
 * 其中对象类型和列表类型可以通过重写实体抽象类的方式实现序列化与反序列化，
 * 而字符串类型、数字类型和布尔类型是基础类型，无法对基础类型扩充序列化和反序列化方法。
 * 因此将这五类类型的序列化和反序列化统一由
 * template <typename T_Type> struct serializer 结构体进行序列化与反序列化的操作
 * 针对字符串类型、数字类型和布尔类型，需要进行模板特例化操作；
 * 针对对象类型和列表类型，就可以调用抽象类的序列化与反序列化方法进行。
 *
 */

#include "extensions/omittable.hpp"
#include "extensions/static_constructable.hpp"
#include "extensions/abstract_object.hpp"
#include "extensions/serializer.hpp"
#include <functional>
#include <sstream>
#include <string.h>
#include <list>


namespace navagraha {
namespace extensions {



// 实体类中字段的封装
template <typename T_Type, // 该字段的类型
         const char * T_Name, // 该字段的名字或Key值
         typename T_Serializer = serializer<T_Type>> // 序列化方法，默认为serializer，该方法通常是为实现json的序列化/反序列化功能
class field : public omittable<T_Type> {
public:
    const char * key = T_Name;

    field() { }

    // copy 构造函数
    field(const field<T_Type, T_Name, T_Serializer> & copyed)
    {
        //this->key = copyed.key;
        if (copyed.omit()) {
            this->get() = copyed.const_get();
        }
    }

    // move 构造函数
    field(field<T_Type, T_Name, T_Serializer> && moved)
    {
        //this->key = moved.key;
        if (moved.omit()) {
            this->get() = moved.const_get();
        }
    }

    // 重载 = 
    field & operator=(const field<T_Type, T_Name, T_Serializer> copyed)
    {
        //this->key = copyed.key;
        if (copyed.omit()) {
            this->get() = copyed.const_get();
        }
        return *this;
    }

    field<T_Type, T_Name, T_Serializer> & operator=(T_Type && obj)
    {
        this->omittable<T_Type>::operator=(obj);

        return *this;
    }

    // 字段的序列化
    void serialize(std::ostringstream & str)
    {
        str.put('"');
        str.write(T_Name, strlen(T_Name));
        str.put('"');
        str.put(':');
        T_Serializer::serialize(this->get(), str);
    }

    // 字段的反序列化
    void deserialize(std::istringstream & str)
    {
        while (str.peek() != ':') {
            str.get();
        }
        T_Serializer::deserialize(this->get(), str);
    }

    // 字段的特例化
    void to_special(abstract_object & obj)
    {
        T_Type special_val = T_Serializer::to_special(obj);
        this->omittable<T_Type>::get() = special_val;
    }

    // 字段的抽象化
    abstract_object to_abstract()
    {
        return serializer<T_Type>::to_abstract(this->get());
    }
};

// 字段序列化函数指针封装
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

// 字段反序列化函数指针封装
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

// 字段序列化工具
void fields_serialize(std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> & serializers,
                      std::ostringstream & str);

}
}

#endif
