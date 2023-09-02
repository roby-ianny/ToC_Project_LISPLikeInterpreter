#ifndef ExecutionVisitor_H
#define ExecutionVisitor_H

#include <vector>
#include <iostream>
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
            Variable* v = s->getVar();          //prendo la variabile dallo statement
            // verifico se la variabile è già presente nel gestore delle variabili
            for (size_t i = 0; i < vars.size() ; i++)
            {
                if (v->getName() == vars[i]->getName())
                {
                    vars[i]->setValue(v->getValue());
                    return; //per uscire dalla funzione
                }
            } //se sono uscito dal ciclo for significa che la variabile non è presente nell'accumulatore
            // allora aggiungo la variabile
            vars.push_back(v);
        }
        
        void visitStatement(const PrintStmt* s){
            NumExpr* ex = s->getExpr();
            ex->accept(this);

            //stampo il numero ottenuto dall'espressione numerica
            std::cout << int_accumulator.back() << std::endl;
            //lo rimuovo dall'accumulatore perché non più necessario
            int_accumulator.pop_back();
        }

        void visitStatement(const InputStmt* s){
            //fase iniziale, prendo in input il valore della variabile
            Variable* v = s->getVar();
            int val;

            std::cout << "Inserire il valore per la variabile " << v->getName() << ": " ;
            
            if(!(std::cin >> val)){              //prendo val in input, se non ricevo un intero restituisco un errore
                throw SemanticError("Invalid Input. Expectet int value");
            }

            v->setValue(val);
            
            //ora che si ha una variabile "completa", ovvero con il valore inserito
            //utilizzo lo stesso meccanismo di setstmt
            for (size_t i = 0; i < vars.size() ; i++)
            {
                if (v->getName() == vars[i]->getName())
                {
                    vars[i]->setValue(v->getValue());
                    return; //per uscire dalla funzione
                }
            }
            vars.push_back(v);
             
        }

        void visitStatement(const IfStmt* s){
            BoolExpr* c = s->getCondition();
            c->accept(this);        //con accept avrà il valore della condition in booleano nell'accumulatore
            if(bool_accumulator.back() == true){
                Block* bl = s->getTrueCase();
                bl->accept(this);
            } else if (bool_accumulator.back() == false)
            {
                Block* bl = s->getFalseCase();
                bl->accept(this);
            } else throw SemanticError("Unexpected error in IfStmt");
            // prima di uscire devo rimuovere la condizione dall'accumulatore
            bool_accumulator.pop_back();
        }

        void visitStatement(const WhileStmt* s){
            // analogamente a quanto visto per If
            BoolExpr* c = s->getCondition();
            c->accept(this);
            Block* loop = s->getLoop();

            while (bool_accumulator.back()==true)
            {
                loop->accept(this);
                bool_accumulator.pop_back(); //rimuovo l'ultima valutazione della condizione
                // rivaluto la condizione
                c->accept(this);
            }
            
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

        void visitNumExpr(const Variable* v){
            /*NB: Bisogna vedere se è stata definita prima!!*/
            for(size_t i = 0; i < vars.size(); i++){
                if (v->getName() == vars[i]->getName())
                {
                    int_accumulator.push_back(vars[i]->getValue());
                    return; //esco dal metodo
                }
            } // Se esco dal ciclo significa che la variabile non c'è, quindi

            throw SemanticError("Undeclared Variable");
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