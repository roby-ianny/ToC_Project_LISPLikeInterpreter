#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "Tokenizer.h"
#include "Exceptions.h"

//Creo la funzione che mi permette di utilizzare più volte la generazione dei token a partire da una stringa
void generateToken(std::string& term, std::vector<Token>& Tokens, int rownumber)
{
    // avere tutti i token generati da un unico "metodo" 
    //inserire il caso "(", ")"
    // Utilizzo una struttura a chiamata ricorsiva per la gestione di parentesi aperte e chiuse

    if (*term.begin() == '(') {
        Tokens.push_back(Token{ Token::LP, Token::id2word[Token::LP]});
        term.erase(0,1);                    //elimino il primo carattere, ovvero la parentesi aperta, così da lasciare solo la parola chiave/numero/idvariabile
        if(!term.empty()) generateToken(term, Tokens, rownumber);        //genero il token del termine senza la parentesi aperta
        return;
    }

    if (term.back() == ')')                 //se il buffer contiene una parentesi chiusa alla fine
    {
        term.pop_back();                    //la elimino da term
        if(!term.empty()) generateToken(term, Tokens, rownumber);        //chiamata ricorsiva, tanto se ha altre parentesi chiuse passa di nuovo da qui
        Tokens.push_back(Token{ Token::RP, Token::id2word[Token::RP]});
        return;                             //esco dal metodo perche non voglio andare avanti
    }
 
    if (term == "SET"){
            Tokens.push_back(Token{ Token::SET, Token::id2word[Token::SET]});
            // term.clear();
        } else if (term == "PRINT"){
            Tokens.push_back(Token{ Token::PRINT, Token::id2word[Token::PRINT]});
            // term.clear();
        } else if (term == "INPUT")
        {
            Tokens.push_back(Token{ Token::INPUT, Token::id2word[Token::INPUT]});
            // term.clear();
        }  else if (term == "IF")
        {
            Tokens.push_back(Token{ Token::IF, Token::id2word[Token::IF]});
            // term.clear();
        } else if (term == "WHILE")
        {
            Tokens.push_back(Token{ Token::WHILE, Token::id2word[Token::WHILE]});
            // term.clear();
        }  else if (term == "ADD")
        {
            Tokens.push_back(Token{ Token::ADD, Token::id2word[Token::ADD]});
            // term.clear();
        }  else if (term == "SUB")
        {
            Tokens.push_back(Token{ Token::SUB, Token::id2word[Token::SUB]});
            // term.clear();
        }  else if (term == "MUL")
        {
            Tokens.push_back(Token{ Token::MUL, Token::id2word[Token::MUL]});
            // term.clear();
        }  else if (term == "DIV")
        {
            Tokens.push_back(Token{ Token::DIV, Token::id2word[Token::DIV]});
            // term.clear();
        }  else if (term == "GT")
        {
            Tokens.push_back(Token{ Token::GT, Token::id2word[Token::GT]});
            // term.clear();
        }  else if (term == "LT")
        {
            Tokens.push_back(Token{ Token::LT, Token::id2word[Token::LT]});
            // term.clear();
        }  else if (term == "EQ")
        {
            Tokens.push_back(Token{ Token::EQ, Token::id2word[Token::EQ]});
            // term.clear();
        }  else if (term == "AND")
        {
            Tokens.push_back(Token{ Token::AND, Token::id2word[Token::AND]});
            // term.clear();
        }  else if (term == "OR")
        {
            Tokens.push_back(Token{ Token::OR, Token::id2word[Token::OR]});
            // term.clear();
        }  else if (term == "NOT")
        {
            Tokens.push_back(Token{ Token::NOT, Token::id2word[Token::NOT]});
            // term.clear();
        }  else if (term == "TRUE")
        {
            Tokens.push_back(Token{ Token::TRUE, Token::id2word[Token::TRUE]});
            // term.clear();
        }  else if (term == "FALSE"){
            Tokens.push_back(Token{ Token::FALSE, Token::id2word[Token::FALSE]});
            // term.clear();
        }  else if ( term == "BLOCK"){
            Tokens.push_back(Token{ Token::BLOCK, Token::id2word[Token::BLOCK]});
            // term.clear();
        }
        /*fin'ora abbiamo visto casi in cui si hanno elementi "costanti", mentre ora dobbiamo fare in modo di convertire elementi variabili in dei Token*/
        // Partiamo quindi dai numeri
        else if (isdigit(term[0]) || term[0]=='-') //se il primo termine della stringa corrisponde a un numero
        {
            size_t i;
            if (term[0] == '-') i = 1;
            else i = 0;
            
            for (; i < term.length(); i++)
            {
                if (!isdigit(term[i])) break;   //se incontro un termine che non è un numero allora interrompo il ciclo   
            }
            if (i == term.length())             //se sono arrivato fino alla fine allora la sequenza corrispone a un numero al quale posso associare un token
            {
                Tokens.push_back(Token{ Token::NUM, term});
            } else {
                std::stringstream msg;
                msg << "Stray character/sequence '" << term <<"' at line " << rownumber ;
                throw LexicalError(msg.str());
            }
           // term.clear();
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
                Tokens.push_back(Token{ Token::VAR, term});
            } else {
                std::stringstream msg;
                msg << "Stray character/sequence '" << term <<"' at line " << rownumber ;
                throw LexicalError(msg.str());
            }
           // term.clear();
        } else {        //In caso in cui il buffer contenga degli elementi non supportati, allora si riporta appunto il conenuto errato
            std::stringstream msg;
            msg << "Stray character/sequence '" << term <<"' at line " << rownumber ;
            throw LexicalError(msg.str());
        }  
};

void Tokenizer::tokenizeInputFile(std::ifstream& inputFile,
     std::vector<Token>& inputTokens){
    // Leggo il file carattere per carattere
    char ch = inputFile.get();  //inizializzo ch con il primo carattere del file
    // ch = inputFile.get();

    //essendo che noi dobbiamo riconoscere sequenze di caratteri, si introduce allora un buffer
    std::string buffer;
    buffer.clear();  

    /* Vecchio "algoritmo" per la generazione dei tokens
    while (!inputFile.eof())                //Finché non arrivo alla fine del filea
    {
        ch = inputFile.get();               //Leggo un carattere dal file
        if(std::isspace(ch)) continue;      //Se il carattere letto è uno spazio
        // considerare il caso !std::isspace(ch)
        else {
            buffer.clear();
            do {
                // rielaborare il caso delle parentesi
                if (ch == '(')
                {
                    // std::cout << "Buffer: " << buffer << std::endl;
                    generateToken(buffer, inputTokens);     //genero un token del buffer e lo ripulisco
                    inputTokens.push_back(Token{ Token::LP, Token::id2word[Token::LP]}); //genero il token della parentesi
                }
                else if (ch == ')')
                {
                    // std::cout << "Buffer: " << buffer << std::endl;
                    generateToken(buffer, inputTokens); 
                    inputTokens.push_back(Token{ Token::RP, Token::id2word[Token::RP]});
                }
                else{               
                    buffer += ch;                   //Aggiugno il carattere al buffer
                }
                ch = inputFile.get();
            } while (!std::isspace(ch) && !inputFile.eof());        //Finchè non incontro uno spazio
            //se quando esco il buffer è ancora "pieno"
            //std::cout << "Buffer: " << buffer << std::endl;

            if(inputTokens.empty()) throw LexicalError("The program is empty");

            generateToken(buffer, inputTokens);

        }        
    }*/

    int rowcnt = 0 ; //creo una variabile che mi traccia il numero di riga

    while (!inputFile.eof())
    {
        if (ch == '\n') rowcnt++;           //se incontro un "invio" allora sono passato a una nuova riga
        if (std::isspace(ch)) {
            ch = inputFile.get();           //avanzo nella lettura del file sennò finirei in un loop infinito
            continue;     //se ho uno spazio skippo un'iterazione del ciclo
        }
        //riempo il buffer finché non incontro uno spazio
        do {                                //prima il "do" perché so già che ch non è uno spazio
            buffer += ch;
            ch = inputFile.get();
        } while (!std::isspace(ch));         //se ch è uno spazio allora sono fuori dal ciclo

        // std::cout << "Buffer: " << buffer << std::endl; 
        generateToken(buffer, inputTokens, rowcnt);
        buffer.clear();

        ch = inputFile.get();               //avanzo nella lettura del file, dovrei anche risolvere il problema dell'evenutale presenza del carattere EOF
    }
    
    if(inputTokens.empty()) throw LexicalError("The program is empty");

}