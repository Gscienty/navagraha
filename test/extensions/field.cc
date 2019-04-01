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

int main()
{
    test1();
    test2();
    return 0;
}
