#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "Statement.h"

class Block{
    void clearMemory(){
        auto i = allocated.begin();
        for (; i != allocated.end(); ++i)
        {
            // *i è l'elemento (nel vettore di Statement) puntato dall'iteratore
            delete(*i);
        }
        
    }

    private:
        std::vector<Statement> allocated;
};

#endif