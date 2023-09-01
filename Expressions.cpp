#include "Expressions.h"
#include "Visitor.h"

void Operator::accept(ExecutionVisitor* v){
    v->visitNumExpr(this);
}

void Number::accept(ExecutionVisitor* v){
    v->visitNumExpr(this);
}

void Variable::accept(ExecutionVisitor* v){
    v->visitNumExpr(this);
}

void BoolConst::accept(ExecutionVisitor* v){
    v->visitBoolExpr(this);
}

void RelOp::accept(ExecutionVisitor* v){
    v->visitBoolExpr(this);
}

void BinaryBoolOp::accept(ExecutionVisitor* v){
    v->visitBoolExpr(this);
}

void NotBoolOp::accept(ExecutionVisitor* v){
    v->visitBoolExpr(this);
}