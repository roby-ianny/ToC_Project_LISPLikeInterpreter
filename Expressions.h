#ifndef EXPR_H
#define EXPR_H

/*Espressioni Booleane e Numeriche*/

#include <string>

class NumExpr{
    public:
        virtual ~NumExpr(){};
        // virtual void accept(Visitor* v) = 0;

};

class Operator : public NumExpr{
    public:
        enum OpCode{ PLUS, MINUS, TIMES, DIV};

        Operator (OpCode o, NumExpr* lop, NumExpr* rop) : op( o ), lo( lop ), ro( rop ) {}
        ~Operator() = default;

        Operator(const Operator& other) = default;
        Operator& operator=(const Operator& other) = default;

        //Metodi di accesso
        OpCode getOp() const{
            return op;
        }

        NumExpr* getLeft() const{
            return lo;
        }

        NumExpr* getRight() const{
            return ro;
        }

        // void accept(Visitor* v) override;

    private:
        OpCode op;
        NumExpr* lo; //left operand
        NumExpr* ro; //right operand
};

class Number : public NumExpr{
    public:
        Number( int v ) : value{ v } {}
        ~Number() = default;

        Number(const Number& other) = default;
        Number& operator=(const Number& other) = default;

        int get_Value() const{
            return value;
        };

        // void accept(Visitor* v) override;

    private:
        int value;

};

class Variable : public NumExpr{
    public:
        Variable( std::string n, int v ) : name( n ), value( v ) {}
        //aggiungo un costruttore con solo id e imposto a 0 il valore iniziale della variabile
        Variable( std::string id) : name{ id }, value{ 0 } {};
        ~Variable() = default;

        Variable(const Variable& other) = default;
        Variable& operator=(const Variable& other) = default;

        std::string getName() const{
            return name;
        }

        int getValue() const{
            return value;
        }

        //void accept(Visitor* v) override;

    private:
        std::string name;
        int value;
};

class BoolExpr{
    public:
        virtual ~BoolExpr(){};
        //virtual void accept(Visitor* v) = 0;
};

class BoolConst : public BoolExpr{
    public:
        enum BoolConstCode { LT, GT, EQ};
        BoolConst(BoolConstCode o, NumExpr* l, NumExpr* r) : op(o), lo(l), ro(r) {}

        ~BoolConst() = default;

        BoolConst(const BoolConst& other) = default;
        BoolConst& operator=(const BoolConst& other) = default;

        BoolConstCode getOp() const{
            return op;
        }

        NumExpr* getLeft() const{
            return lo;
        }

        NumExpr* getRight() const{
            return ro;
        }

    private:
        BoolConstCode op;
        NumExpr* lo;
        NumExpr* ro;
};

/*
class BoolOp : public BoolExpr{
    private:
        virtual ~BoolExpr(){};
    public:
};

Siccome ho due operatori booleani binari, e uno unario, utilizzo due  classi 
distinte invece che usare BoolOp

*/

/* Definisco la classe per gli operatori booleani binari, AND e OR*/
class BinaryBoolOp : public BoolExpr{
    private:
        enum BinBoolOpCode{ AND, OR};
        BinaryBoolOp(BinBoolOpCode o, BoolExpr* l, BoolExpr* r) : op( o ), lo( l ), ro( r ){}

        ~BinaryBoolOp() = default;

        BinaryBoolOp(const BinaryBoolOp& other) = default;
        BinaryBoolOp& operator=(const BinaryBoolOp& other) = default;
    public:
        BinBoolOpCode op;
        BoolExpr* lo;
        BoolExpr* ro;
};


/* Definisco la classe per l'operatore unario NOT */
class NotBoolOp : public BoolExpr{
    public:
        // enum NotOpCode{ NOT};
        NotBoolOp(/*NotOpCode o,*/ BoolExpr* e) : /*op( o ),*/ expr( e ) {}

        ~NotBoolOp() = default;

        NotBoolOp(const NotBoolOp& other) = default;
        NotBoolOp& operator=(const NotBoolOp& other) = default;
    private:
        //NotOpCode op;
        BoolExpr* expr;
    
};

#endif