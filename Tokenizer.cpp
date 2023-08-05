#include <string>
#include <sstream>

#include "Tokenizer.h"
#include "Exceptions.h"

void tokenizeInputFile(std::ifstream& inputFile, std::vector<Token> inputTokens)
{
    // Leggo il file carattere per carattere
    char ch;
    ch = inputFile.get();

    //essendo che noi dobbiamo riconoscere sequenze di caratteri, si introduce allora un buffer
    std::string buffer;

    while(!inputFile.eof()){

        buffer += ch;

        if (std::isspace(ch)){
            //skippo lo spazio bianco
            buffer.clear; //svuoto il buffer se incontro uno spazio
            ch = inputFile.get();
            continue;   //lo faccio utilizzando continue
        }

        if (buffer == 'SET'){
            inputTokens.push_back(Token{ Token::SET, Token::id2word[Token::SET]});
            buffer.clear;
        } else if (buffer == 'PRINT'){
            inputTokens.push_back(Token{ Token::PRINT, Token::id2word[Token::PRINT]});
            buffer.clear;
        } else if (buffer == 'INPUT')
        {
            inputTokens.push_back(Token{ Token::INPUT, Token::id2word[Token::INPUT]});
            buffer.clear;
        } else if {
            inputTokens.push_back(Token{ Token::LP, Token::id2word[Token::LP]});
            buffer.clear;
        } else if (buffer == ')'){
            inputTokens.push_back(Token{ Token::LP, Token::id2word[Token::LP]});
            buffer.clear;
        }
    }
}