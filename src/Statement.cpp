#include "Expressions.h"
#include "Statement.h"
#include "Visitor.h"

void SetStmt::accept(ExecutionVisitor* v){
    v->visitStatement(this);
}

void PrintStmt::accept(ExecutionVisitor* v){
    v->visitStatement(this);
}

void InputStmt::accept(ExecutionVisitor* v){
    v->visitStatement(this);
}

void IfStmt::accept(ExecutionVisitor* v){
    v->visitStatement(this);
}

void WhileStmt::accept(ExecutionVisitor* v){
    v->visitStatement(this);
}