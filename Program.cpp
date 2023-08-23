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
    } else {
        throw ParseError("Unexpected Token");
        return nullptr;
    }
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
Statement* Program::recursiveParse(std::vector<Token>::const_iterator& itr)
{
    /*
    //Uno statement inizia con una parentesi aperta e termina con una parentesi chiusa
    if (itr->tag == Token::LP) {    //Partiamo dal fatto che ogni statement inizia con una parentesi aperta
        Devo analizzare una grammatica non ambigua, allora il parsing si effettua in maniera monodirezionale, a differenza di quanto
        visto con il parser di YetAnotherInterpreter, in questo caso allora si avrà comunque un parser ricorsivo, ma strutturato in modo diverso.
        Il risultato finale deve essere una sequenza si statements, se abbiamo uno statement che ne contiene altri, in questo caso appariranno prima quelli più interni
        fino ad arrivare a quello più esterno, per poi passare allo statement successivo
        safe_next(itr);                 //passo all'elemenento successivo della token stream
        if (itr->tag == Token::LP)      //Se incontro un'altra parentesi vuol dire che vi sono degli statement "interni"
        {
            recursiveParse(itr);        //Allora come detto inizialmente, bisogna generare prima gli statement più interni
        }
        // verifico la presenza di una parola chiave
        switch (itr->tag)
        {
        case Token::SET :
            safe_next(itr);
            if (itr->tag == Token::VAR)
        {}}         
            break;
        case Token::PRINT :
            safe_next(itr);
            switch (itr->tag);
            //chiamare anche qui il parser specifico per le espressioni numeriche
            //TODO: implementare un gestore delle variabil
            NumExpr* nexpr = parseNumExpr (itr); 
        
        default:
            break;
        }        
    }
    */
}