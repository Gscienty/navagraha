#include "extensions/field.hpp"
#include <sstream>
#include <string>
#include <iostream>

char test_name[] = "foo";

void test1()
{
    std::ostringstream str;
    navagraha::extensions::field<int, test_name> field;
    field = 20;
    field.serialize(str);

    std::cout << str.str() << std::endl;
}

void test2()
{
    std::ostringstream str;
    navagraha::extensions::field<std::string, test_name> field;
    field = "lish";
    field.serialize(str);

    std::cout << str.str() << std::endl;
}

void deserialize_test1()
{
    std::istringstream str("foo: 123");
    navagraha::extensions::field<int, test_name> field;
    field.deserialize(str);

    std::cout << field.omit() << std::endl;
    std::cout << field.get() << std::endl;
}

void deserialize_test2()
{
    std::istringstream str("foo: \"\\\"lish\\\"\"");
    navagraha::extensions::field<std::string, test_name> field;
    field.deserialize(str);

    std::cout << field.omit() << std::endl;
    std::cout << field.get() << std::endl;
}

int main()
{
    test1();
    test2();

    deserialize_test1();
    deserialize_test2();
    return 0;
}
