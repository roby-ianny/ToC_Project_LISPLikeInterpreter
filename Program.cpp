#include <sstream>
#include <string>
#include "Exceptions.h"
#include "Expressions.h"
#include "Statement.h"
#include "Block.h"
#include "Program.h"


//Parser per le espressioni numeriche
NumExpr* Program::parseNumExpr(std::vector<Token>::const_iterator& itr){
    // Caso in cui ci fosse una num_expr con operatore
    if (itr->tag == Token::LP)
    {
        safe_next(itr);
            Operator::OpCode op;
            switch (itr->tag)
            {
            case Token::ADD: op = Operator::PLUS; break;
            case Token::SUB: op = Operator::MINUS; break;
            case Token::MUL: op = Operator::TIMES; break;
            case Token::DIV: op = Operator::DIV; break;    
            default: 
                throw ParseError("Unrecognized operator");
            }

            //eseguo il parsing del primo operando
            safe_next(itr);
            NumExpr* lo = parseNumExpr(itr);

            //eseguo il parsing del secondo operando
            safe_next(itr);
            NumExpr* ro = parseNumExpr(itr);
            
            //verifico la corretta presenza della parentesi chiusa
            safe_next(itr);
            if (itr->tag == Token::RP){
                //restituisco un puntatore a una numexpr di tipo operator
                return new Operator(op, lo, ro);    
            }
            else{
                throw ParseError("Unexpected Token");
            }
            
    } else if (itr->tag == Token::NUM){             //nel caso ci fosse un numero viene restituito un numero
        return new Number(std::stoi(itr->word));    //converto in numero il contenuto della parola
    } else if (itr->tag == Token::VAR)
    {
        // return new Variable(itr->word);          ancora da implementare correttamente un gestore dellev variabili
    }

    //nel caso non fossi in nessuno di questi casi allora vi è un errore
    throw ParseError("Unexpected Token");
    return nullptr;
}

//Parse per le espressioni booleani
BoolExpr* Program::parseBoolExpr(std::vector<Token>::const_iterator& itr){
    //in maniera analoga a quanto fatto per parseNumExpr si realizza anche questo metodo di classe
    if (itr->tag == Token::LP)
    {
        safe_next(itr);
        switch (itr->tag)
        {
        case Token::LT :
        {
            RelOp::RelOpCode op = RelOp::LT ;
            safe_next(itr);
            NumExpr* lo = parseNumExpr(itr);
            safe_next(itr);
            NumExpr* ro = parseNumExpr(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) return new RelOp(op, lo, ro);
            else throw ParseError("Unexpected token");
            break;
        }
        case Token::GT :
        {
            RelOp::RelOpCode op = RelOp::GT ;
            safe_next(itr);
            NumExpr* lo = parseNumExpr(itr);
            safe_next(itr);
            NumExpr* ro = parseNumExpr(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) return new RelOp(op, lo, ro);
            else throw ParseError("Unexpected token");
            break;
        }
        case Token::EQ :
        {
            RelOp::RelOpCode op = RelOp::EQ ;
            safe_next(itr);
            NumExpr* lo = parseNumExpr(itr);
            safe_next(itr);
            NumExpr* ro = parseNumExpr(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) return new RelOp(op, lo, ro);
            else throw ParseError("Unexpected token");
            break;
        }
        case Token::AND :
        {
            BinaryBoolOp::BinBoolOpCode op = BinaryBoolOp::AND ;
            safe_next(itr);
            BoolExpr* lo = parseBoolExpr(itr);
            safe_next(itr);
            BoolExpr* ro = parseBoolExpr(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) return new BinaryBoolOp(op, lo, ro);
            else throw ParseError("Unexpected token");
            break;
        }
        case Token::OR : 
        {
            BinaryBoolOp::BinBoolOpCode op = BinaryBoolOp::OR ;
            safe_next(itr);
            BoolExpr* lo = parseBoolExpr(itr);
            safe_next(itr);
            BoolExpr* ro = parseBoolExpr(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) return new BinaryBoolOp(op, lo, ro);
            else throw ParseError("Unexpected token");
            break;
        }
        case Token::NOT :
        {
            safe_next(itr);
            BoolExpr* e = parseBoolExpr(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) return new NotBoolOp(e);
            else throw ParseError("Unexpected token");
        }
        default:
            {
            throw ParseError("Unrecognized Operator");
            break;
            }
        }
    }
    else if (itr->tag == Token::TRUE)  return new BoolConst(BoolConst::TRUE);
    else if (itr->tag == Token::FALSE) return new BoolConst(BoolConst::FALSE);
    else {
        throw ParseError("Unexpected Token");
        return nullptr;
    }

       
}


void Program::parseBlock(std::vector<Token>::const_iterator& itr, Block* b){
    if (itr->tag == Token::LP)
    {
        safe_next(itr);
        if (itr->tag == Token::BLOCK)
        {
            safe_next(itr);
            while (itr->tag != Token::RP);
            {
                if (itr->tag == Token::LP)
                {
                    b->push_back(recursiveParse(itr));
                    safe_next(itr);
                } else {
                    throw ParseError("Unexpected Token in BLOCK");
                }            
            }
        }
        else {
            b->push_back(recursiveParse(itr)); 
        }
        
    }
    
}


//Parser a discesa ricorsiva
Statement* Program::recursiveParse(std::vector<Token>::const_iterator& itr) {
    /*if (itr->tag == Token::LP)
    {
        safe_next(itr);*/
        switch (itr->tag)
        {
        case Token::SET :
        {
            safe_next(itr);
            if (itr->tag == Token::VAR){
                /*NB implementare il gestore delle variabili*/
                Variable* var = new Variable(itr->word);
                safe_next(itr);
                NumExpr* ex = parseNumExpr(itr);
                safe_next(itr);
                if (itr->tag == Token::RP){
                    return makeSet(ex, var);
                    break;
                }
                else throw ParseError("Mismatched Parenthesis");
            }else throw ParseError("SET statement, expected variable token");
            
        }
        case Token::PRINT :
        {
            safe_next(itr);
            NumExpr* ex = parseNumExpr(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) makePrint(ex);
            else throw ParseError("Mismatched Parenthesis"); 
            break;
        }
        case Token::INPUT :
        {
            safe_next(itr);
            if (itr->tag == Token::VAR) {
                Variable* v = new Variable(itr->word);
                safe_next(itr);
                if (itr->tag == Token::RP) return makeInput(v) ;
                else throw ParseError("Mismatched Parenthesis") ;          
            } else throw ParseError("INPUT statement, expected variable token");
            break;
        }
        case Token::IF :
        {
            safe_next(itr);
            BoolExpr* expr = parseBoolExpr(itr);
            safe_next(itr);
            Block* tr = new Block();
            parseBlock(itr, tr);
            safe_next(itr);
            Block* fls = new Block();
            parseBlock(itr, fls);
            if(itr->tag == Token::RP) return makeIf(expr, tr, fls);
            else throw ParseError("Mismatched Parenthesis");
            break;
        }
        case Token::WHILE :
        {
            safe_next(itr);
            BoolExpr* expr = parseBoolExpr(itr);
            safe_next(itr);
            Block* bl;
            parseBlock(itr, bl);
            safe_next(itr);
            if(itr->tag == Token::RP) return makeWhile(expr, bl);
            else throw ParseError("Mismatched Parenthesis");
            break;
        }
        default:
            throw ParseError("Invalid Token");
            return nullptr;
            break;
        }
    /*}
    else {
        throw ParseError("Mismatched Parenthesis");
        return nullptr;
    }
    */
}