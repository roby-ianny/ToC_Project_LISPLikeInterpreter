#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include "Block.h"
#include "Expressions.h"

//Forward Declaration
class ExecutionVisitor; 
class Block;

class Statement{
    public:
        virtual ~Statement() {};
        virtual void accept(ExecutionVisitor* v) = 0;
};


class SetStmt : public Statement {
    public: 
        SetStmt(NumExpr* e, Variable* v) : expr( e ), var( v ) {}
        ~SetStmt(){
            delete(expr);
            delete(var);
        }

        SetStmt(const SetStmt& other) = default;
        SetStmt& operator=(const SetStmt& other) = default;

        void accept(ExecutionVisitor* v) override;

        Variable* getVar() const{
            return var;
        }

        NumExpr* getExpr() const{
            return expr;
        }

    private:
        NumExpr* expr;
        Variable* var;
};

class PrintStmt : public Statement {
    public:
        PrintStmt(NumExpr* expr) : e( expr ) {}
        
        ~PrintStmt(){
            delete(e);
        }

        PrintStmt(const PrintStmt& other) = default;
        PrintStmt& operator=(const PrintStmt& other) = default;

        NumExpr* getExpr () const {
            return e;
        }

        void accept(ExecutionVisitor* v) override;
    private:
        NumExpr* e;
};

class InputStmt : public Statement {
    public: 
        InputStmt(Variable* v) : var ( v ){}
        ~InputStmt(){
            delete(var);
        }

        InputStmt(const InputStmt& other) = default;
        InputStmt& operator=(const InputStmt& other) = default;

        void accept(ExecutionVisitor* v) override;

        Variable* getVar() const{
            return var;
        }

    private:
        Variable* var;
};

class IfStmt : public Statement {
    public: 
        IfStmt(BoolExpr* expression, Block* t, Block* f) : bexpr( expression ), true_case( t ), false_case(f) {}
        ~IfStmt(){
            delete(bexpr);
            delete(true_case);
            delete(false_case);
        }

        IfStmt(const IfStmt& other) = default;
        IfStmt& operator=(const IfStmt& other) = default;

        void accept(ExecutionVisitor* v)override;

        BoolExpr* getCondition() const{
            return bexpr;
        }

        Block* getTrueCase() const{
            return true_case;
        }

        Block* getFalseCase() const{
            return false_case;
        }

    private:
        BoolExpr* bexpr;
        Block* true_case;
        Block* false_case;
};


class WhileStmt : public Statement {
    public: 
        WhileStmt(BoolExpr* expression, Block* bl) : bexpr( expression ), b ( bl ) {}
        ~WhileStmt(){
            delete(bexpr);
            delete(b);
        }

        WhileStmt(const WhileStmt& other) = default;
        WhileStmt& operator=(const WhileStmt& other) = default;

        void accept(ExecutionVisitor* v) override;

        BoolExpr* getCondition() const{
            return bexpr;
        }

        Block* getLoop() const{
            return b;
        }

    private:
        BoolExpr* bexpr;
        Block* b;
};

#endif