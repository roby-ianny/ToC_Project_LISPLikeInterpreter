#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>

#include "Exceptions.h"
#include "Token.h"
#include "Expressions.h"
#include "Statement.h"
#include "Block.h"

//Program svolge il ruolo di ParseExpression visto nell'esempio della lezione
class Program{
    public:
        Program(Block& b) : mb{ b } {};

        /*Factory method per gli statement*/
        Statement* operator()(const std::vector<Token>& TokenStream){
            auto tokenItr = TokenStream.begin();
            streamEnd = TokenStream.end();
            Statement* stmt = recursiveParse(tokenItr);
            return stmt;
        }

        /*Factory Method per generare gli oggetti*/
        Statement* makeSet(NumExpr* e, Variable* v){
            Statement* s = new SetStmt(e, v);
            mb.push_back(s);
            return s;
        }

        Statement* makePrint(NumExpr* exp){
            Statement* s = new PrintStmt(exp);
            mb.push_back(s);
            return s;
        }

        Statement* makeInput(Variable* v){
            Statement* s = new InputStmt(v);
            mb.push_back(s);
            return s;
        }

        Statement* makeIf(BoolExpr* exp, Block* b){
            Statement* s = new IfStmt(exp, b);
            mb.push_back(s);
            return s;
        }

        Statement* makeWhile(BoolExpr* e, Block* b){
            Statement* s = new WhileStmt(e, b);
            mb.push_back(s);
            return s;
        }

    private:
        //costante che indica la fine dei token nel vector
        std::vector<Token>::const_iterator streamEnd;

        //Block è l'equivalente dell'expression manager
        Block& mb;
        
        Statement* recursiveParse(std::vector<Token>::const_iterator& itr);             //parser degli statements

        NumExpr* parseNumExpr(std::vector<Token>::const_iterator& itr);                 //parser espressioni numeriche

        BoolExpr* parseBoolExpr(std::vector<Token>::const_iterator& itr);               //parser espressioni booleane

        void safe_next(std::vector<Token>::const_iterator& itr){
            if (itr == streamEnd){
                throw ParseError("Unexpected end of input");
            }
            ++itr;
        }
};


#endif