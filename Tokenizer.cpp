#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "Tokenizer.h"
#include "Exceptions.h"

//Creo la funzione che mi permette di utilizzare più volte la generazione dei token a partire da una stringa
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

        /*fin'ora abbiamo visto casi in cui si hanno elementi "costanti", mentre ora dobbiamo fare in modo di convertire elementi variabili in dei Token*/
        // Partiamo quindi dai numeri
        else if (isdigit(term[0]) ) //se il primo termine della stringa corrisponde a un numero
        {
            size_t i;
            for (i = 0; i < term.length(); i++)
            {
                if (!isdigit(term[i])) break;   //se incontro un termine che non è un numero allora interrompo il ciclo   
            }
            if (i == term.length())             //se sono arrivato fino alla fine allora la sequenza corrispone a un numero al quale posso associare un token
            {
                Tokens.push_back(Token{ Token::NUM, Token::id2word[Token::NUM]});
            }
            /*else
            verrà gestita l'eccezione            
            */
        }

        //Rimane quindi l'ultimo caso, ovvero quello in cui il vi è corrispondenza con il nome di una variabile
        //analogamente a quanto fatto per i numeri, utilizzo isalpha per verificare che la variabile rispetti la condizione
        else if (isalpha(term[0]))
        {
            size_t i;
            for(i = 0; i < term.length(); i++)
            {
                if (!isalpha(term[i])) break;                
            }
            if (i == term.length())
            {
                Tokens.push_back(Token{ Token::VAR, Token::id2word[Token::VAR]});
            }
            /*else
            verrà gestita l'eccezione
            */
        }
        /*else
        verrà gestita l'eccezione in cui non si hanno corrispondenze
        */      
};

void Tokenizer::tokenizeInputFile(std::ifstream& inputFile,
     std::vector<Token>& inputTokens){
    // Leggo il file carattere per carattere
    char ch;
    ch = inputFile.get();

    //essendo che noi dobbiamo riconoscere sequenze di caratteri, si introduce allora un buffer
    std::string buffer;
    buffer.clear();

    while(!inputFile.eof())
    {
        if (isspace(ch)){
            ch = inputFile.get();
            buffer.clear();
            continue;
        }
        //finchè non si incontra uno spazio, analizzo un pezzo di testo
        do {
            ch = inputFile.get();
            buffer += ch;

            if (ch == '('){     //Se incappo in una parentesi aperta
                std::cout << "Il buffer contiene: " << buffer << std::endl;
                buffer.pop_back();
                generateToken(buffer, inputTokens);     //genero il token di quel che c'era prima della parentesi
                inputTokens.push_back(Token{ Token::LP, Token::id2word[Token::LP]});        //genero il token della parentesi
            }
            else if (ch == ')'){                        //stessa cosa per l'altra parentesi
                std::cout << "Il buffer contiene: " << buffer << std::endl;
                buffer.pop_back();
                generateToken(buffer, inputTokens);
                inputTokens.push_back(Token{ Token::RP, Token::id2word[Token::RP]});
            }
        } while (!std::isspace(ch));
        //eliminati i casi delle parentesi, si genera il token della porzione di testo
        generateToken(buffer, inputTokens);

    }
}