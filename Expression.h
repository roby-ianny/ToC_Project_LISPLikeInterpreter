#ifndef EXPRESSION_H
#define EXPRESSION_H

class NumExpr{
    public:
        //virtual...
};

class Operator : public NumExpr{
    public:
    private:
        NumExpr lo; //left operand
        NumExpr ro; //right operand
};

class Number : public NumExpr{
    public:
    private:

};

class Variable : public NumExpr{
    public:
    private:
};

class BoolExpr{
    public:
        //virtual ...
    private:
};

class RelOp : public BoolExpr{
    public:
    private:
        NumExpr lo;
        NumExpr ro;
};

class BoolConst : public BoolExpr{
    private:
    public:
};

class BoolOp : public BoolExpr{
    private:
    public:
};



#endif