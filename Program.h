#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>

#include "Exceptions.h"
#include "Token.h"
#include "Block.h"
#include "Statement.h"

//Program svolge il ruolo di ParseExpression visto nell'esempio della lezione
class Program{
    public:
        Program(Block& b) : mb{ b } {};

        Statement* operator()(const std::vector<Token>& TokenStream){
            auto tokenItr = TokenStream.begin();
            streamEnd = TokenStream.end();
            Statement* stmt = recursiveParse(tokenItr);
            return stmt;
        }


    private:
        //costante che indica la fine dei token nel vector
        std::vector<Token>::const_iterator streamEnd;

        //Block è l'equivalente dell'expression manager
        Block& mb;
        Statement* recursiveParse(std::vector<Token>::const_iterator& tokenItr);

        void safe_next(std::vector<Token>::const_iterator& itr){
            if (itr == streamEnd){
                throw ParseError("Unexpected end of input");
            }
            ++itr;
        }
};


#endif