#include <string>
#include <sstream>
#include <vector>

#include "Tokenizer.h"
#include "Exceptions.h"

void generateToken(std::string term, std::vector<Token> Tokens)
{
    if (term == "SET"){
            Tokens.push_back(Token{ Token::SET, Token::id2word[Token::SET]});
            term.clear();
        } else if (term == "PRINT"){
            Tokens.push_back(Token{ Token::PRINT, Token::id2word[Token::PRINT]});
            term.clear();
        } else if (term == "INPUT")
        {
            Tokens.push_back(Token{ Token::INPUT, Token::id2word[Token::INPUT]});
            term.clear();
        }  else if (term == "IF")
        {
            Tokens.push_back(Token{ Token::IF, Token::id2word[Token::IF]});
            term.clear();
        } else if (term == "WHILE")
        {
            Tokens.push_back(Token{ Token::WHILE, Token::id2word[Token::WHILE]});
            term.clear();
        }  else if (term == "ADD")
        {
            Tokens.push_back(Token{ Token::ADD, Token::id2word[Token::ADD]});
            term.clear();
        }  else if (term == "SUB")
        {
            Tokens.push_back(Token{ Token::SUB, Token::id2word[Token::SUB]});
            term.clear();
        }  else if (term == "MUL")
        {
            Tokens.push_back(Token{ Token::MUL, Token::id2word[Token::MUL]});
            term.clear();
        }  else if (term == "DIV")
        {
            Tokens.push_back(Token{ Token::DIV, Token::id2word[Token::DIV]});
            term.clear();
        }  else if (term == "GT")
        {
            Tokens.push_back(Token{ Token::GT, Token::id2word[Token::GT]});
            term.clear();
        }  else if (term == "LT")
        {
            Tokens.push_back(Token{ Token::LT, Token::id2word[Token::LT]});
            term.clear();
        }  else if (term == "EQ")
        {
            Tokens.push_back(Token{ Token::EQ, Token::id2word[Token::EQ]});
            term.clear();
        }  else if (term == "AND")
        {
            Tokens.push_back(Token{ Token::AND, Token::id2word[Token::AND]});
            term.clear();
        }  else if (term == "OR")
        {
            Tokens.push_back(Token{ Token::OR, Token::id2word[Token::OR]});
            term.clear();
        }  else if (term == "NOT")
        {
            Tokens.push_back(Token{ Token::NOT, Token::id2word[Token::NOT]});
            term.clear();
        }  else if (term == "TRUE")
        {
            Tokens.push_back(Token{ Token::TRUE, Token::id2word[Token::TRUE]});
            term.clear();
        }  else if (term == "FALSE")
        {
            Tokens.push_back(Token{ Token::FALSE, Token::id2word[Token::FALSE]});
            term.clear();
        }  
};

void tokenizeInputFile(std::ifstream& inputFile, std::vector<Token> inputTokens)
{
    // Leggo il file carattere per carattere
    char ch;
    ch = inputFile.get();

    //essendo che noi dobbiamo riconoscere sequenze di caratteri, si introduce allora un buffer
    std::string buffer;
    buffer.clear();

    while(!inputFile.eof()){
        
        while (!std::isspace(ch)){
            buffer += ch;
            ch = inputFile.get();
        }
        
}