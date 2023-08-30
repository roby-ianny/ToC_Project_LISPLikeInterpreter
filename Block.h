#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "Expressions.h"
#include "Statement.h"

class Statement; //Forward declaration

class Block{
    public:
        Block() {
            std::vector<Statement*> st;     //creo un vector vuoto
            allocated = st;                 //allocated lo pongo uguale al vector vuoto
        }
        ~Block(){
            clearMemory();
        }

        //elimino costruttori di copia e assegnamento
        Block(const Block& other) = delete;
        Block& operator=(const Block& other) = delete;

        void clearMemory(){
            auto i = allocated.begin();
            for(; i != allocated.end(); ++i){
                delete(*i);
                //NB: Così non vengono deallocati elementi come NumExpr, BoolExpr, Variabili...
            }
            allocated.resize(0);
        }

        std::vector<Statement*> getAllocated() const{
            return allocated;
        }

        // Definisco questo metodo da utilizzare nel parser, questo perché evito dipendenze cicliche in questo modo
        void push_back(Statement* s){
            allocated.push_back(s);
        }

    private:
        std::vector<Statement*> allocated;
};

#endif
