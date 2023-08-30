#ifndef ExecutionVisitor_H
#define ExecutionVisitor_H

#include <vector>
#include "Block.h"

class ExecutionVisitor {
    public:
        ExecutionVisitor() : vars{ } , int_accumulator{ }, bool_accumulator{ } {}
        
        void visitBlock(const Block* b){
            for (Statement* st : b->getAllocated()){
                //esegue tutte le istruzioni contenute negli statements
            }
        }

        void visitStatement(const SetStmt* s){

        }
        
        void visitStatement(const PrintStmt* s){

        }

        void visitStatement(const InputStmt* s){

        }

        void visitStatement(const IfStmt* s){

        }

        void visitStatement(const WhileStmt* s){

        }

        void visitNumExpr(const Operator* op){

        }

        void visitNumExpr(const Number* n){

        }

        void visitNumExpr(const Variable *v){

        }

        void vistBoolExpr(const BoolConst* bc){

        }

        void visitBoolExpr(const RelOp* ro){

        }

        void visitBoolExpr(const BinaryBoolOp* op){

        }

        void visitBoolExpr(const NotBoolOp* op){
            
        }

    private:
        std::vector<Variable*>        vars;     //creo un gestore delle variabili
        std::vector<int>   int_accumulator;     //gestore dei numeri interi per le espressioni numeriche
        std::vector<bool> bool_accumulator;     //gestore delle espressioni booleane (utile per i cicli annidati)
};

#endif