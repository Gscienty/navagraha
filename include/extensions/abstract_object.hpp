#ifndef _NAVAGRAHA_EXTENSION_ABSTRACT_OBJECT_H
#define _NAVAGRAHA_EXTENSION_ABSTRACT_OBJECT_H

#include <string>
#include <map>
#include <vector>

namespace navagraha {
namespace extensions {


// 字段类型描述
enum abstract_object_type {
    abstract_object_type_obj,
    abstract_object_type_list,
    abstract_object_type_str,
    abstract_object_type_num,
    abstract_object_type_boolean
};

// 实体抽象类
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

    // 序列化操作，返回是自身的引用
    abstract_object & serialize(std::ostringstream & str);

    // 反序列化操作，返回的是自身的引用
    abstract_object & deserialize(std::istringstream & str);

    // 抽象化操作，返回是本身
    abstract_object to_abstract();

    // 特例化操作，返回是特例化的结果，抽象实体类的特例化结果依旧是自身
    static abstract_object to_special(abstract_object & obj);
};


}
}

#endif
