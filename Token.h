#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// I token della nsotra grammatica sono i seguenti
// - Parentesi aperte e chiuse
// - Operatori ADD, SUB, MUL, DIV
// - Operatori Booleani GT, LT, EQ, AND, OR, NOT
// - Assegnazione e stampa: SET, PRINT, INPUT
// - Blocchi iterativi e condizionali: IF, WHILE
// - Valori booleani: TRUE, FALSE
// - numeri (definito con le regole number)
// - variabili (definite con le regole variabile id)

// Un token è una coppia ID - parola dove:
// - ID è un identificatovo attribuito al Token
// - parola è la stringa corrispondente al Token

struct Token
{
    // usiamo come identificativi univoci delle constexpr che assegnano un numero costante a un certo valore
    static constexpr int SET    = 0;
    static constexpr int PRINT  = 1;
    static constexpr int INPUT  = 2;
    static constexpr int IF     = 3;
    static constexpr int WHILE  = 4;
    static constexpr int ADD    = 5;
    static constexpr int SUB    = 6;
    static constexpr int MUL    = 7;
    static constexpr int DIV    = 8;
    static constexpr int GT     = 9;
    static constexpr int LT     = 10;
    static constexpr int EQ     = 11;
    static constexpr int AND    = 12;
    static constexpr int OR     = 13;
    static constexpr int NOT    = 14;
    static constexpr int TRUE   = 15;
    static constexpr int FALSE  = 16;
    static constexpr int LP     = 17;
    static constexpr int RP     = 18;
    static constexpr int NUM    = 19;
    static constexpr int VAR    = 20;

    static constexpr char* id2word[]{   //Vettore per passare dal termine in input al token corrispondente
        "SET", "PRINT", "INPUT", "IF", "WHILE", "ADD", "SUB", "MUL", "DIV",
        "GT", "LT", "EQ", "AND", "OR", "NOT", "TRUE", "FALSE", "LP", "RP", "NUM", "VAR"
    };

    Token(int t, const char* w) : tag{ t }, word{ w } {}
    Token(int t, std::string w) : tag{ t }, word{ w } {}

    int tag; //tag costituisce l'id nella coppia id - parola
    std::string word; //word definisce la parolan nella coppia
};

//overload dell'operatore di inserimento per i token
std::ostream& operator<<(std::ostream& os, const Token& t);

#endif
