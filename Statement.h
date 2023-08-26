#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include "Block.h"
#include "Expressions.h"

//Forward Declaration
class Visitor; 
class Block;

class Statement{
    public:
        virtual ~Statement() {};
        // virtual void accept(Visitor* v) = 0;
};


class SetStmt : public Statement {
    public: 
        SetStmt(NumExpr* e, Variable* v) : expr( e ), var( v ) {}
        ~SetStmt() = default;

        SetStmt(const SetStmt& other) = default;
        SetStmt& operator=(const SetStmt& other) = default;
    private:
        NumExpr* expr;
        Variable* var;
};

class PrintStmt : public Statement {
    public:
        PrintStmt(NumExpr* expr) : e( expr ) {}
        
        ~PrintStmt() = default;
        PrintStmt(const PrintStmt& other) = default;
        PrintStmt& operator=(const PrintStmt& other) = default;

    private:
        NumExpr* e;
};

class InputStmt : public Statement {
    public: 
        InputStmt(Variable* v) : var ( v ){}
        ~InputStmt() = default;

        InputStmt(const InputStmt& other) = default;
        InputStmt& operator=(const InputStmt& other) = default;
    private:
        Variable* var;
};

class IfStmt : public Statement {
    public: 
        IfStmt(BoolExpr* expression, Block* t, Block* f) : bexpr( expression ), true_case( t ), false_case(f) {}
        ~IfStmt() = default;

        IfStmt(const IfStmt& other) = default;
        IfStmt& operator=(const IfStmt& other) = default;
    private:
        BoolExpr* bexpr;
        Block* true_case;
        Block* false_case;
};


class WhileStmt : public Statement {
    public: 
        WhileStmt(BoolExpr* expression, Block* bl) : bexpr( expression ), b ( bl ) {}
        ~WhileStmt() = default;

        WhileStmt(const WhileStmt& other) = default;
        WhileStmt& operator=(const WhileStmt& other) = default;
    private:
        BoolExpr* bexpr;
        Block* b;
};

#endif