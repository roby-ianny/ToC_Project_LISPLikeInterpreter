#ifndef ExecutionVisitor_H
#define ExecutionVisitor_H

#include <vector>
#include <iostream>
#include <string>
#include "Block.h"
#include "Statement.h"
#include "Expressions.h"
#include "Exceptions.h"

class ExecutionVisitor {
    public:
        ExecutionVisitor() : vars{ } , int_accumulator{ }, bool_accumulator{ } {}
        
        void visitBlock(const Block* b){
            // std::cout << "Visiting Block" << std::endl;
            for (Statement* st : b->getAllocated()){
                // std::cout << "Visiting ";
                st->accept(this);
            }
            return;
        }

        void visitStatement(const SetStmt* s){
            // std::cout << "SetStatement " << std::endl;
            std::string name = s->getVar()->getName();  // prendo il nome della variabile dal set statement
            NumExpr* e = s->getExpr();                  // prendo l'espressione numerica
            e->accept(this);                            // calcolo il valore dell'espressione numerica
            Variable* v = new Variable(name, int_accumulator.back());
            int_accumulator.pop_back();                 // elimino il valore dall'accumulatore
            for (size_t i = 0; i < vars.size() ; i++)
            {
                if (v->getName() == vars[i]->getName()) // la variabile era già stata dichiarata
                {
                    vars.erase(vars.begin() + i);       // elimino la variabile dal gestore
                    vars.push_back(v);                  // reinserisco la variabile col nuovo valore
                    return;                             // esco dal metodo
                }
            } //se sono uscito dal ciclo for significa che la variabile non è presente nell'accumulatore
            vars.push_back(v);                          // inserisco la variabile nel gestore
        }
        
        void visitStatement(const PrintStmt* s){
            // std::cout << "PrintStatement " << std::endl;
            NumExpr* ex = s->getExpr();
            ex->accept(this);

            //stampo il numero ottenuto dall'espressione numerica
            std::cout << int_accumulator.back() << std::endl;
            //lo rimuovo dall'accumulatore perché non più necessario
            int_accumulator.pop_back();
        }

        void visitStatement(const InputStmt* s){
            //fase iniziale, prendo in input il valore della variabile
            // std::cout << "InputStatement " << std::endl;
            std::string name = s->getVar()->getName();
            int val;

            std::cout << "Inserire il valore per la variabile " << name << ": " ;
            
            if(!(std::cin >> val)){              //prendo val in input, se non ricevo un intero restituisco un errore
                throw SemanticError("Invalid Input. Expected int value");
            }
            
            Variable* v = new Variable(name, val);

            //ora che si ha una variabile "completa", ovvero con il valore inserito
            //utilizzo lo stesso meccanismo di setstmt
            for (size_t i = 0; i < vars.size() ; i++)
            {
                if (v->getName() == vars[i]->getName())
                {
                    vars.erase(vars.begin() + i);       // elimino la variabile "obsoleta"
                    vars.push_back(v);
                    return;                             //per uscire dalla funzione
                }
            }
            vars.push_back(v);
        }

        void visitStatement(const IfStmt* s){
            // std::cout << "IfStatement " << std::endl;
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
            // std::cout << "WhileStatement" << std::endl;
            // analogamente a quanto visto per If
            Block* loop = s->getLoop();

            BoolExpr* c = s->getCondition();
            c->accept(this);

            while (bool_accumulator.back()==true)
            {
                // std::cout << "Entering in loop (again?)" << std::endl;
                loop->accept(this);
                bool_accumulator.pop_back(); //rimuovo l'ultima valutazione della condizione
                // rivaluto la condizione
                c->accept(this);
            }
            bool_accumulator.pop_back();
            return;
        }

        void visitNumExpr(const Operator* op){
            // std::cout << "Visiting Operator " << std::endl;
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
                    throw SemanticError("ERROR in evaluator: Division by zero.");
                }
                else int_accumulator.push_back(lval/rval);
                break;
            default:
                throw SemanticError("SEMANTIC ERRROR: Invalid Operator");
                break;
            }
        }

        void visitNumExpr(const Number* n){
            // std::cout << "Visiting Number " << std::endl;
            int_accumulator.push_back(n->get_Value());  //mette il numero nell'accumulatore
        }

        void visitNumExpr(const Variable* v){
            /*NB: Bisogna vedere se è stata definita prima!!*/
            // std::cout << "Visiting Variable " << std::endl;
            for(size_t i = 0; i < vars.size(); i++){
                if (v->getName() == vars[i]->getName())
                {
                    // std::cout << "Variable Exists: " << vars[i]->getName() << " " << vars[i]->getValue() << std::endl;
                    int_accumulator.push_back(vars[i]->getValue());
                    return; //esco dal metodo
                }
            } // Se esco dal ciclo significa che la variabile non c'è, quindi
            throw SemanticError("Undeclared Variable");
        }

        void visitBoolExpr(const BoolConst* bc){
            // std::cout << "Visiting BoolConst " << std::endl;
            if (bc->getValue() == BoolConst::TRUE ) bool_accumulator.push_back(true);
            else if (bc->getValue() == BoolConst::FALSE) bool_accumulator.push_back(false);
            else SemanticError("Invalid bool constant");
            
        }

        void visitBoolExpr(const RelOp* ro){

            // std::cout << "Visiting Relational Operator " << std::endl;
            NumExpr* left = ro->getLeft();
            left->accept(this);
            int lval = int_accumulator.back(); 
            int_accumulator.pop_back();

            NumExpr* right = ro->getRight();
            right->accept(this);
            int rval = int_accumulator.back(); 
            int_accumulator.pop_back();
            

            switch (ro->getOp())
            {
            case RelOp::LT :
                bool_accumulator.push_back(lval < rval);
                break;
            case RelOp::GT :
                bool_accumulator.push_back(lval > rval);
                break;
            case RelOp::EQ :
                bool_accumulator.push_back(lval == rval);
                break;
            default:
                SemanticError("Invalid Relational Operator");
                break;
            }
        }

        void visitBoolExpr(const BinaryBoolOp* op){

            // std::cout << "Visiting Binary Bool Operator " << std::endl;

            BoolExpr* left = op->getLeft();
            left->accept(this);
            bool rval = bool_accumulator.back(); bool_accumulator.pop_back();
            BoolExpr* right = op->getRight();
            right->accept(this);
            bool lval = bool_accumulator.back(); bool_accumulator.pop_back();          
            
            switch (op->getOpCode())
            {
            case BinaryBoolOp::AND :
                bool_accumulator.push_back(rval && lval);
                break;
            case BinaryBoolOp::OR :
                bool_accumulator.push_back(rval || lval);
                break;            
            default:
                SemanticError("Invalid Boolean Operator");
                break;
            }
        }

        void visitBoolExpr(const NotBoolOp* op){

            // std::cout << "Visiting Not Bool Operator " << std::endl;

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