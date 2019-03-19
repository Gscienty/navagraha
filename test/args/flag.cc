#include "arg/arg_def.hpp"
#include <iostream>

int main(int argc, char ** argv)
{
    navagraha::arg::arg_def flag1("f1", 3);
    navagraha::arg::arg_def flag2("f2", 0);

    bool ret = navagraha::arg::transfer(argc, argv);

    std::cout << ret
        << ' '
        << flag1.argument().used()
        << ' '
        << flag2.argument().used()
        << std::endl;
    return 0;
}
