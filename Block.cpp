#include "Expressions.h"
#include "ProgramElements.h"
#include "Visitor.h"

void Block::accept(ExecutionVisitor* v){
    v->visitBlock(this);
}
