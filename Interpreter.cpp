#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

#include "Exceptions.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Statement.h"
#include "StatementManager.h"
#include "Parser.h"
#include "Visitor.h"

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
        std::cerr << "Non posso aprire il file " << argv[1] << std::endl
        std::cerr << e.what() << std::endl ;
        return EXIT_FAILURE
    }
    
    /* FASE 1 - Tokenizzazione */

}