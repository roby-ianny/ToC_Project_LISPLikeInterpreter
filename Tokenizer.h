#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include<fstream>

#include "Token.h"

//Il tokenizer contiene la sequenza di token acquisiti dal file di input
class Tokenizer
{
    public:
    std::vector<Token> operator()(std::ifstream& inputfile){
        std::vector<Token> inputTokens;
        tokenizeInputFile(inputfile, inputTokens); 
        return inputTokens;
    }

    private:
    //il metodo genera la sequenza di token a partire dal file di input
    void tokenizeInputFile(std::ifstream& inputFile, std::vector<Token> inputTokens);
};

#endif