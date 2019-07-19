#ifndef _NAVAGRAHA_EXTENSION_SERIALIZER_H
#define _NAVAGRAHA_EXTENSION_SERIALIZER_H

#include <string>
#include <sstream>
#include "extensions/abstract_object.hpp"

namespace navagraha {
namespace extensions {

// 字段类型统一序列化/反序列化工具结构体
template <typename T_Type> struct serializer {
    // 序列化操作
    static void serialize(T_Type & obj, std::ostringstream & str)
    {
        obj.serialize(str);
    }

    // 反序列化操作
    static void deserialize(T_Type & obj, std::istringstream & str)
    {
        obj.deserialize(str);
    }

    // 抽象化操作
    static abstract_object to_abstract(T_Type & obj)
    {
        return obj.to_abstract();
    }

    // 特例化操作
    static T_Type to_special(abstract_object & obj)
    {
        return T_Type::to_special(obj);
    }
};

// 字符串的 serializer 的模板特例化
template <> struct serializer<std::string> {
    // 字符串类型的序列化操作
    static void serialize(std::string & obj, std::ostringstream & str)
    {
        // TODO 字符串中，对特定字符的转义处理
        str.put('"');
        str.write(obj.data(), obj.size());
        str.put('"');
    }

    // 字符串的反序列化操作
    static void deserialize(std::string & obj, std::istringstream & str)
    {
        char c;
        while (c = str.get(), c != '"');
        for (c = str.get(); c != '"' || (*obj.rbegin() == '\\'); c = str.get()) {
            obj.push_back(c);
        }
    }

    // 字符串的抽象化操作
    static abstract_object to_abstract(std::string & obj)
    {
        return abstract_object(obj);
    }

    // 字符串的特例化操作
    static std::string to_special(abstract_object & obj)
    {
        if (obj.type != abstract_object_type_str) {
            return std::string();
        }
        return obj.str;
    }
};

// int 类型的 serializer 模板特例化
template <> struct serializer<int> {
    // int 的序列化操作
    static void serialize(int & obj, std::ostringstream & str)
    {
        std::string number = std::to_string(obj);
        str.write(number.data(), number.size());
    }

    // int 的反序列化操作
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

    // int 的抽象化操作
    static abstract_object to_abstract(int & obj)
    {
        return abstract_object(obj);
    }

    // int 的特例化操作
    static int to_special(abstract_object & obj)
    {
        if (obj.type != abstract_object_type_num) {
            return 0;
        }
        return obj.val.num;
    }
};

// bool 的 serializer 模板特例化
template <> struct serializer<bool> {
    // bool 的序列化操作
    static void serialize(bool & obj, std::ostringstream & str)
    {
        std::string boolean(obj ? "true" : "false");
        str.write(boolean.data(), boolean.size());
    }

    // bool 的反序列化操作
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

    // bool 的抽象化操作
    static abstract_object to_abstract(bool & obj)
    {
        return abstract_object(obj);
    }

    // bool 的特例化操作
    static bool to_special(abstract_object & obj)
    {
        if (obj.type != abstract_object_type_boolean) {
            return false;
        }
        return obj.val.boolean;
    }
};

}
}

#endif
