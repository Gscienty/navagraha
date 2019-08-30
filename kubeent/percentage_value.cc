#include "kubeent/percentage_value.hpp"

namespace navagraha {
namespace kubeent {

char PERCENTAGE_VALUE[] = "_";

void percentage_value::bind(extensions::serializer_helper &)
{

}

percentage_value & percentage_value::deserialize(std::istringstream & str)
{
    while (str.peek() != '"' && (str.peek() < '0' || '9' < str.peek())) {
        str.ignore();
    }

    if (str.peek() == '"') {
        str.ignore();
        this->value = 0;

        while ('0' <= str.peek() && str.peek() <= '9') {
            this->value *= 10;
            this->value += str.get() - '0';
        }
        while (str.get() != '"');
    }
    else {
        while ('0' <= str.peek() && str.peek() <= '9') {
            this->value *= 10;
            this->value += str.get() - '0';
        }
    }

    return *this;
}

percentage_value & percentage_value::serialize(std::ostringstream & str)
{
    std::string val = std::to_string(this->value);
    str.write(val.data(), val.size());

    return *this;
}

}
}
