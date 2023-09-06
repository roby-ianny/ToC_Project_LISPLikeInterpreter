#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>
#include <iostream>

#include "Exceptions.h"
#include "Token.h"
#include "Expressions.h"
#include "ProgramElements.h"

//Program svolge il ruolo di ParseExpression visto nell'esempio della lezione
class Program{
    public:
        Program(Block& b) : mb{ b } {};

        /*Factory method per l'albero sintattico*/
        Block* operator()(const std::vector<Token>& TokenStream){
            auto tokenItr = TokenStream.begin();
            streamEnd = TokenStream.end();
            Block* bl = &mb;
            parseBlock(tokenItr, bl);
            return bl;
        }

        /*Factory Method per generare gli oggetti*/
        Statement* makeSet(NumExpr* e, Variable* v){
            Statement* s = new SetStmt(e, v);
            // push_back(s);
            std::cout << "Made set statement" << std::endl;
            return s;
        }

        Statement* makePrint(NumExpr* exp){
            Statement* s = new PrintStmt(exp);
            // push_back(s);
            std::cout << "Made print statement" << std::endl;
            return s;
        }

        Statement* makeInput(Variable* v){
            Statement* s = new InputStmt(v);
            // push_back(s);
            std::cout << "Made input statement" << std::endl;
            return s;
        }

        Statement* makeIf(BoolExpr* exp, Block* t, Block* f){
            Statement* s = new IfStmt(exp, t, f );
            // push_back(s);
            std::cout << "Made if statement" << std::endl;
            return s;
        }

        Statement* makeWhile(BoolExpr* e, Block* b){
            Statement* s = new WhileStmt(e, b);
            // push_back(s);
            std::cout << "Made while statement" << std::endl;
            return s;
        }

    private:
        //costante che indica la fine dei token nel vector
        std::vector<Token>::const_iterator streamEnd;

        //Block è l'equivalente dell'expression manager
        Block& mb;

        void parseBlock(std::vector<Token>::const_iterator& itr, Block* b);             //parser del blocco che serve per restituire l'albero sintattico

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