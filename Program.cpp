#include <sstream>
#include <string>

#include "Program.h"
#include "Token.h"
#include "Exceptions.h"
#include <string>

//Parser per le espressioni numeriche
NumExpr* parseNumExpr(std::vector<Token>::const_iterator& itr){
    /*DA DEFINIRE*/    
}
//Parse per le espressioni booleani
BoolExpr* parseBoolExpr(std::vector<Token>::const_iterator& itr){
    /*DA DEFINIRE*/
}

//Parser a discesa ricorsiva
Statement* Program::recursiveParse(std::vector<Token>::const_iterator& itr)
{
    //Uno statement inizia con una parentesi aperta e termina con una parentesi chiusa
    if (itr->tag == Token::LP) {    //Partiamo dal fatto che ogni statement inizia con una parentesi aperta
        /* Devo analizzare una grammatica non ambigua, allora il parsing si effettua in maniera monodirezionale, a differenza di quanto
        visto con il parser di YetAnotherInterpreter, in questo caso allora si avrà comunque un parser ricorsivo, ma strutturato in modo diverso.
        Il risultato finale deve essere una sequenza si statements, se abbiamo uno statement che ne contiene altri, in questo caso appariranno prima quelli più interni
        fino ad arrivare a quello più esterno, per poi passare allo statement successivo*/
        safe_next(itr);                 //passo all'elemenento successivo della token stream
        if (itr->tag == Token::LP)      //Se incontro un'altra parentesi vuol dire che vi sono degli statement "interni"
        {
            recursiveParse(itr);        //Allora come detto inizialmente, bisogna generare prima gli statement più interni
        }
        // verifico la presenza di una parola chiave
        switch (itr->tag)
        {
        case Token::SET :
            safe_next(itr);
            if (itr->tag == Token::VAR)
            {
                Variable* v = new Variable{itr->word};  //mi segno il nome della variabile
                safe_next(itr);                         //passo all'elemento successivo
                if (itr->tag == Token::NUM)             //se assegno direttamente un numero
                {
                    NumExpr* num = new Number(std::stoi(itr->word)) ; //genero l'espressione numerica
                    //allora in questo caso posso generare il set statement
                    return makeSet(num, v);             //alloca lo statement nell0albero 
                }
                else if (itr->tag == Token::LP)
                {
                    // parsing specifico per le espressioni numeriche
                }
                else {
                    throw ParseError("Unexpected Token");   //restituisco un messaggio di errore
                    return nullptr;                         //ritorna il nullpointer
                }
            }            
            break;
        case Token::PRINT :
            safe_next(itr);
            switch (itr->tag);
            //chiamare anche qui il parser specifico per le espressioni numeriche
            //TODO: implementare un gestore delle variabil
            NumExpr* nexpr = parseNumExpr (itr); 
        
        default:
            break;
        }        
    }
    
}