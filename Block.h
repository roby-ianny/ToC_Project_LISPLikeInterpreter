#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "Statement.h"
#include "Expressions.h"

class Statement;//Forward declaration per evitare problemi di dipendenza cicliche
class SetStmt;
class WhilStmt;


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
        Statement* makeSet(NumExpr* e, Variable* v){
            Statement* s = new SetStmt(e, v);
            allocated.push_back(s);
            return s;
        }

        Statement* makeWhile(BoolExpr* e, Block* b){
            Statement* s = new WhileStmt(e, b);
            allocated.push_back(s);
            return s;
        }

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
