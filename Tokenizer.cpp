#include <string>
#include <sstream>
#include <vector>

#include "Tokenizer.h"
#include "Exceptions.h"

void tokenizeInputFile(std::ifstream& inputFile, std::vector<Token> inputTokens)
{
    // Leggo il file carattere per carattere
    char ch;
    ch = inputFile.get();

    //essendo che noi dobbiamo riconoscere sequenze di caratteri, si introduce allora un buffer
    std::string buffer;
    buffer.clear();

    while(!inputFile.eof()){

        if (ch == '(')
        {
            inputTokens.push_back(Token{ Token::LP, Token::id2word[Token::LP]});
            buffer.clear();
        } else if (ch == ')')
        {
            inputTokens.push_back(Token{ Token::RP, Token::id2word[Token::RP]});
            buffer.clear();
        } else if (std::isspace(ch)) {
            buffer.clear
        }
        
        buffer += ch;

        if (buffer == "SET"){
            inputTokens.push_back(Token{ Token::SET, Token::id2word[Token::SET]});
            buffer.clear();
        } else if (buffer == "PRINT"){
            inputTokens.push_back(Token{ Token::PRINT, Token::id2word[Token::PRINT]});
            buffer.clear();
        } else if (buffer == "INPUT")
        {
            inputTokens.push_back(Token{ Token::INPUT, Token::id2word[Token::INPUT]});
            buffer.clear();
        }  else if (buffer == "IF")
        {
            inputTokens.push_back(Token{ Token::IF, Token::id2word[Token::IF]});
            buffer.clear();
        } else if (buffer == "WHILE")
        {
            inputTokens.push_back(Token{ Token::WHILE, Token::id2word[Token::WHILE]});
            buffer.clear();
        }  else if (buffer == "ADD")
        {
            inputTokens.push_back(Token{ Token::ADD, Token::id2word[Token::ADD]});
            buffer.clear();
        }  else if (buffer == "SUB")
        {
            inputTokens.push_back(Token{ Token::SUB, Token::id2word[Token::SUB]});
            buffer.clear();
        }  else if (buffer == "MUL")
        {
            inputTokens.push_back(Token{ Token::MUL, Token::id2word[Token::MUL]});
            buffer.clear();
        }  else if (buffer == "DIV")
        {
            inputTokens.push_back(Token{ Token::DIV, Token::id2word[Token::DIV]});
            buffer.clear();
        }  else if (buffer == "GT")
        {
            inputTokens.push_back(Token{ Token::GT, Token::id2word[Token::GT]});
            buffer.clear();
        }  else if (buffer == "LT")
        {
            inputTokens.push_back(Token{ Token::LT, Token::id2word[Token::LT]});
            buffer.clear();
        }  else if (buffer == "EQ")
        {
            inputTokens.push_back(Token{ Token::EQ, Token::id2word[Token::EQ]});
            buffer.clear();
        }  else if (buffer == "AND")
        {
            inputTokens.push_back(Token{ Token::AND, Token::id2word[Token::AND]});
            buffer.clear();
        }  else if (buffer == "OR")
        {
            inputTokens.push_back(Token{ Token::OR, Token::id2word[Token::OR]});
            buffer.clear();
        }  else if (buffer == "NOT")
        {
            inputTokens.push_back(Token{ Token::NOT, Token::id2word[Token::NOT]});
            buffer.clear();
        }  else if (buffer == "TRUE")
        {
            inputTokens.push_back(Token{ Token::TRUE, Token::id2word[Token::TRUE]});
            buffer.clear();
        }  else if (buffer == "FALSE")
        {
            inputTokens.push_back(Token{ Token::FALSE, Token::id2word[Token::FALSE]});
            buffer.clear();
        }  
    }
}