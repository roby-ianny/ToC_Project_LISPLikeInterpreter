#ifndef STATEMENT_H
#define STATEMENT_H

class Visitor; //Da definire poi per l'analisi semantica

class Statement{
    public:
        virtual ~Statement() {};
};

class WhileStmt : public Statement {
    public: 
        //il costruttore per passaggio di parametro
        WhileStmt(NumExpr* expression) : nexpr( expression ) {}
        ~WhileStmt() = default;

        WhileStmt(const WhileStmt& other) = default;
        WhileStmt& operator=(const WhileStmt& other) = default;

    private:    
        NumExpr* nexpr;
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

class InputStmt : public Statement {
    public: 
        InputStmt(Variable* v) : var ( v ){}
        ~InputStmt() = default;

        InputStmt(const InputStmt& other) = default;
        InputStmt& operator=(const InputStmt& other) = default;
    private:
        Variable* var;
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

class IfStmt : public Statement {
    public: 
        IfStmt(BoolExpr* expression, Block* bl) : bexpr( expression ), b ( bl ) {}
        ~IfStmt() = default;

        IfStmt(const IfStmt& other) = default;
        IfStmt& operator=(const IfStmt& other) = default;
    private:
        BoolExpr* bexpr;
        Block* b;
};


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

class RelOp : public BoolExpr{
    public:
        enum RelOpCode { LT, GT, EQ};
        RelOp(RelOpCode o, NumExpr* l, NumExpr* r) : op(o), lo(l), ro(r) {}

        ~RelOp() = default;

        RelOp(const RelOp& other) = default;
        RelOp& operator=(const RelOp& other) = default;

        RelOpCode getOp() const{
            return op;
        }

        NumExpr* getLeft() const{
            return lo;
        }

        NumExpr* getRight() const{
            return ro;
        }

    private:
        RelOpCode op;
        NumExpr* lo;
        NumExpr* ro;
};

class BoolConst : public BoolExpr{
    private:
    public:
};

class BoolOp : public BoolExpr{
    private:
    public:
};

/* Definisco la classe per gli operatori booleani binari, AND e OR
class BinaryBoolOp : public BoolOp{

};
*/

/* Definisco la classe per l'operatore unario NOT
class NotBoolOp : public BoolOp{

};
*/


#endif