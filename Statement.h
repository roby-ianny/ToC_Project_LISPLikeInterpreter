#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>
#include "Expression.h"

class Program{
    private:
        // Block b; ? 
};

class Block{
    private:
        std::vector<Statement> inputStatements;
};

class Statement{
    public:
        //virtual ...
};

class PrintStmt : public Statement {
    public: 
        //virtual...
    private:
        NumExpr nexpr;
};

class SetStmt : public Statement {
    public: 
        //virtual...
    private:
        Variable var;
};

class InputStmt : public Statement {
    public: 
        //virtual...
    private:
        Variable var;
};

class WhileStmt : public Statement {
    public: 
        //virtual...
    private:
        BoolExpr bexpr;
        Block b;
};

class IfStmt : public Statement {
    public: 
        //virtual...
    private:
        BoolExpr bexpr;
        Block b;
};





#endif