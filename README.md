# Progetto
L'obiettivo del progetto è quello di realizzare un interprete per un linguaggio LISP-LIKE in C++.
Ciò avviene in 3 fasi: 
## Analisi Lessicale
In questa fase si prende il file di input e si genera una sequenza di Token, ovvero una sequenza di coppie id-word che servono da ponte tra il "programma in ingresso" e il parser, che si occuperà dell'analisi lessicale.

La libreria Token.h definisce i token per i vari elementi del "linguaggio", mentre Token.cpp contiene l'overloading dell'operatore di inserimento.

Tokenizer invece si occupa di convertire le parore in ingresso in una sequenza di Token, occupandosi della conversione di numeri e di variabili.