#include <sstream>

#include "Token.h"

std::ostream& operator<<(std::ostream& os, const Token& t)
{
    std::stringstream tmp;
    tmp << t.tag << " : " << t.word;
    os << tmp.str();
    return os;
}