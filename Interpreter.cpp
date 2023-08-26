#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

#include "Exceptions.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Statement.h"
#include "Block.h"
#include "Program.h"

int main(int argc, char *argv[])
{
    if (argc < 2){  //il numero di argomenti deve essere minimo 2 (nome dell'eseguibile e nome del file)
        std::cerr << "File non specificato!" << std::endl;
        std::cerr << "Utilizzo: " << argv[0] << " <nome_file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream inputFile;
    //dichiaro la variabile inputFile, ora controllo se il file esiste per evitare crash
    try
    {
        inputFile.open(argv[1]); // inputfile corrisponde con il file passato da riga di comando
    }
    catch(const std::exception& e)
    {
        std::cerr << "Non posso aprire il file " << argv[1] << std::endl;
        std::cerr << e.what() << std::endl ;
        return EXIT_FAILURE;
    }
    
    /* FASE 1 - Tokenizzazione 
    File interessati: Token.h, Token.cpp, Tokenizer.h, Tokenizer.cpp
    */

    Tokenizer tokenize;
    std::vector<Token> inputTokens;

    try
    {
        inputTokens = std::move(tokenize(inputFile));
        inputFile.close();  //dopo aver ottenuto la token sequence il file non è più necessario
    }
    catch(LexicalError& le)
    {
        std::cerr << "Errore in fase di analisi lessicale" << std::endl;
        std::cerr << le.what() << '\n';
        return EXIT_FAILURE;
    }
    catch(std::exception& exc){
        std::cerr << "Impossibile leggere dal file: " << argv[1] << std::endl;
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Stampa dei tokens
    for(Token t : inputTokens){
        std::cout << t << std::endl;
    }

    /*Fase 2 - Parsing
    File interessati: Expression.h, Expression.cpp, Statement.h, Statement.cpp, Program.h, Program.cpp interessati*/
    
    //Creo il node manager, ovvero ciò che mi costituisce il block
    Block main_bl;

    //Creo il function object per il parsing
    Program parse{ main_bl };

    try {
        Statement* st = parse(inputTokens);
        std::cout << "Parsing terminato" << std::endl;
        //PrintVisitor p = new PrintVisitor();
        //std::cout << "L'espressione letta è ";
    } catch (ParseError& pe){
        std::cerr << "Errore in parsing" << std::endl;
        std::cerr << pe.what() << std::endl ;
    } /*catch(std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }
 
    return EXIT_SUCCESS;
*/

}