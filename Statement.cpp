#include "Statement.h"
#include "Visitor.h"

void SetStmt::accept(ExecutionVisitor* v){
    v->visitStatement(this);
}