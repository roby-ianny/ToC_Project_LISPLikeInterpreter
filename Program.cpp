#include <sstream>
#include <string>

#include "Program.h"
#include "Token.h"
#include "Exceptions.h"

//Parser a discesa ricorsiva

Statement* Program::recursiveParse(std::vector<Token>::const_iterator& itr)
{
    //Uno statement inizia con una parentesi aperta e termina con una parentesi chiusa
    if (itr->tag == Token::LP) {
        safe_next(itr); //passo all'elemenento successivo della token stream
    }
    
}