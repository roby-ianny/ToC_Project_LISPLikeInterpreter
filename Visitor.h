#ifndef ExecutionVisitor_H
#define ExecutionVisitor_H

#include <vector>
#include "Block.h"
#include "Statement.h"
#include "Expressions.h"
#include "Exceptions.h"

class ExecutionVisitor {
    public:
        ExecutionVisitor() : vars{ } , int_accumulator{ }, bool_accumulator{ } {}
        
        void visitBlock(const Block* b){
            for (Statement* st : b->getAllocated()){
                st->accept(this);
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
            // Propago la visita ai due operandi
            NumExpr* left = op->getLeft();
            left->accept(this);
            NumExpr* right = op->getRight();
            right->accept(this);
            //Prelevo i valori dall'accumulatore
            int rval = int_accumulator.back(); int_accumulator.pop_back();
            int lval = int_accumulator.back(); int_accumulator.pop_back();

            switch (op->getOp())
            {
            case Operator::PLUS:
                int_accumulator.push_back(lval + rval);
                break;
            case Operator::MINUS:
                int_accumulator.push_back(lval-rval);
                break;
            case Operator::TIMES:
                int_accumulator.push_back(lval*rval);
                break;
            case Operator::DIV:
                if (rval == 0)
                {
                    SemanticError("SEMANTIC ERROR: Can't divide by zero");
                }
                else int_accumulator.push_back(lval/rval);
                break;
            default:
                SemanticError("SEMANTIC ERRROR: Invalid Operator");
                break;
            }
        }

        void visitNumExpr(const Number* n){
            int_accumulator.push_back(n->get_Value());  //mette il numero nell'accumulatore
        }

        void visitNumExpr(const Variable *v){
            int_accumulator.push_back(v->getValue());   //mette il valore attuale della variabile nell'accumulatore
        }

        void visitBoolExpr(const BoolConst* bc){
            if (bc->getValue() == BoolConst::TRUE ) bool_accumulator.push_back(true);
            else if (bc->getValue() == BoolConst::FALSE) bool_accumulator.push_back(false);
            else SemanticError("Invalid bool constant");
            
        }

        void visitBoolExpr(const RelOp* ro){
            NumExpr* left = ro->getLeft();
            left->accept(this);
            NumExpr* right = ro->getRight();
            right->accept(this);

            int rval = int_accumulator.back(); int_accumulator.pop_back();
            int lval = int_accumulator.back(); int_accumulator.pop_back();

            switch (ro->getOp())
            {
            case RelOp::LT :
                bool_accumulator.push_back(rval < lval);
                break;
            case RelOp::GT :
                bool_accumulator.push_back(rval > lval);
                break;
            case RelOp::EQ :
                bool_accumulator.push_back(rval == lval);
                break;
            default:
                SemanticError("Invalid Relational Operator");
                break;
            }
        }

        void visitBoolExpr(const BinaryBoolOp* op){
            BoolExpr* left = op->getLeft();
            left->accept(this);
            BoolExpr* right = op->getRight();
            right->accept(this);

            bool rval = bool_accumulator.back(); bool_accumulator.pop_back();
            bool lval = bool_accumulator.back(); bool_accumulator.pop_back();

            switch (op->getOpCode())
            {
            case BinaryBoolOp::AND :
                bool_accumulator.push_back(rval || lval);
                break;
            case BinaryBoolOp::OR :
                bool_accumulator.push_back(rval && lval);
                break;            
            default:
                SemanticError("Invalid Boolean Operator");
                break;
            }
        }

        void visitBoolExpr(const NotBoolOp* op){
            BoolExpr* o = op->getOperand();
            o->accept(this);
            bool val = bool_accumulator.back(); bool_accumulator.pop_back();

            bool_accumulator.push_back(!val);
        }

    private:
        std::vector<Variable*>        vars;     //creo un gestore delle variabili
        std::vector<int>   int_accumulator;     //gestore dei numeri interi per le espressioni numeriche
        std::vector<bool> bool_accumulator;     //gestore delle espressioni booleane (utile per i cicli annidati)
};

#endif