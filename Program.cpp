#include <sstream>
#include <string>

#include "Program.h"
#include "Token.h"
#include "Exceptions.h"
#include <string>

//Parser per le espressioni numeriche
NumExpr* Program:: parseNumExpr(std::vector<Token>::const_iterator& itr){
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

//Parser a discesa ricorsiva
Statement* Program::recursiveParse(std::vector<Token>::const_iterator& itr) {
    if (itr->tag == Token::LP)
    {
        safe_next(itr);
        switch (itr->tag)
        {
        case Token::BLOCK :
        {
            std::cout << "entering block" << std::endl;
            safe_next(itr);
            recursiveParse(itr);
            safe_next(itr);
            if (itr->tag == Token::RP)          //sono arrivato alla fine del blocco di istruzioni
            {
                std::cout << "exiting block" << std::endl;
                break;
            }
            else recursiveParse(itr);           //se non sono arrivato in fondo eseguo il parsing degli altri statement
        }
        case Token::SET :
        {
            safe_next(itr);
            if (itr->tag == Token::VAR){
                /*NB implementare il gestore delle variabili*/
                Variable* var = new Variable(itr->word);
                safe_next(itr);
                NumExpr* ex = parseNumExpr(itr);
                safe_next(itr);
                if (itr->tag == Token::RP) return makeSet(ex, var);
                else throw ParseError("Mismatched Parenthesis");
            }else throw ParseError("SET statement, expected variable token");
            break;
        }
        case Token::PRINT :
        {
            safe_next(itr);
            NumExpr* ex = parseNumExpr(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) makePrint(ex);
            else throw ParseError("Mismatched Parenthesis"); 
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
        }
        case Token::IF :
        {
            safe_next(itr);
            BoolExpr* expr = parseBoolExpr(itr);
            safe_next(itr);
            Statement* tr = recursiveParse(itr);
            safe_next(itr);
            Statement* fls = recursiveParse(itr);
            if(itr->tag == Token::RP) return makeIf(expr, tr, fls);
            else throw ParseError("Mismatched Parenthesis");
        }
        case Token::WHILE :
        {
            safe_next(itr);
            BoolExpr* expr = parseBoolExpr(itr);
            safe_next(itr);
            Statement* bl = recursiveParse(itr);
            safe_next(itr);
            if(itr->tag == Token::RP) return makeWhile(expr, bl);
            else throw ParseError("Mismatched Parenthesis");
        }
        default:
            throw ParseError("Invalid Token");
            return nullptr;
            break;
        }
    }
    else {
        throw ParseError("Mismatched Parenthesis");
        return nullptr;
    }
    
}