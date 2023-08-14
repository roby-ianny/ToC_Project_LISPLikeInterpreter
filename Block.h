#ifndef BLOCK_H
#define BLOCK_H

#include "Statement.h"
#include <vector>

class Statement;

class Block{
    public:
        Block() = default;
        ~Block(){
            clearMemory();
        }

        //elimino costruttori di copia e assegnamento
        Block(const Block& other) = delete;
        Block& operator=(const Block& other) = delete;

        /*Factory Method per generare gli oggetti*/

        void clearMemory(){
            auto i = allocated.begin();
            for(; i != allocated.end(); ++i){
                delete(*i);
                //NB: Così non vengono deallocati elementi come NumExpr, BoolExpr, Variabili...
            }
            allocated.resize(0);
        }

    private:
        std::vector<Statement*> allocated;
};

#endif
