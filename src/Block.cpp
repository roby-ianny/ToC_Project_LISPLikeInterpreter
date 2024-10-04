#include "Expressions.h"
#include "Statement.h"
#include "Block.h"
#include "Visitor.h"

void Block::accept(ExecutionVisitor* v){
    v->visitBlock(this);
}
