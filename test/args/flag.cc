#include "cli_arg/process_collection.hpp"
#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "cli_arg/process_helper.hpp"
#include <iostream>
#include <sstream>

char TEST_FLAG1[] = "flag1";
char TEST_FLAG2[] = "flag2";

class test_process : public navagraha::cli_arg::abstract_process<test_process> {
private:
    navagraha::cli_arg::arg<TEST_FLAG1, 0> flag1;
    navagraha::cli_arg::arg<TEST_FLAG2, 1> flag2;
public:
    test_process()
    {
        this->flag2.require(this->flag1);
    }

    virtual void bind(navagraha::cli_arg::process_helper<test_process> & helper) override
    {
        helper
            .add(this->flag1)
            .add(this->flag2);
    }

    virtual int execute() override
    {
        std::cout << "Success" << std::endl;
        return 0;
    }

    virtual bool satisfy() const override
    {
        return this->flag1.used() && this->flag2.used();
    }
};

int main(int argc, char ** argv)
{
    std::ostringstream str;

    
    navagraha::cli_arg::process_collection(argc, argv)
        .add(test_process())
        .result();
    return 0;
}
