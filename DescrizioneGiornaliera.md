# LISPLikeInterpreter
Progetto di Informatica e Computazione - Università degli studi di Genova

## Giorno 1 - 2/08/2023
- Lettura delle dispense sul progetto
- Analisi dell'interprete realizzato durante le esercitazioni in modo da avere un modello di partenza

## Giorno 2 - 3/08/2023
Cerchiamo bene di capire come funziona questo interprete e dividiamo in vari step la sua creazione.

Il professore ha fatto la seguente suddivisione in tre parti, che andiamo ora ad analizzare:

*Analisi Lessicale:* L'analisi lessicale corrisponde al tokenizer visto nelle esercitazioni, è la componente che prende il file in input, ignora gli spazi e genera una sequenza di token che vengono poi elaborati nella fase di analisi sintattica.

*Analisi Sintattica:* L'analisi sintattica è quella che controlla se effettivamente ciò che i è stato dato in input è corretto oppure no. Dopo il parsing viene generato un albero sintattico (v. derivazione nelle CFG). In caso di errore mi viene restituito un messaggio specifico per quel tipo di errore

*Analisi Semantica:* È la componente che effettivamente si occupa dell'esecuzione del programma ricevuto. Esegue quindi le istruzioni riportate, genera nuove variabili e si occupa dell'I/O. Oltre a ciò deve restituirmi anche i vari errori "a runtime", come per esempio le divisioni per 0.

### Struttura dei file
Sulla falsa riga di quanto fornito nelle dispense e di quanto visto a lezione, il nostro interprete dovrà avere la seguente struttura:

- Exceptions.h
    - Libreria per il gestore delle eccezioni
- Expression.h
    - Libreria contenente la definizione delle espressioni, nel nostro caso invece saranno degli statement block quindi potremmo anche chiamarlo "Statement.h"
- Expression.cpp
    - Contiene i metodi che restituiscono i token corretti quando si utilizza il visitor
- Expressionmanager.h
    - È una libreria che implementa una componente che si occupa di deallocare correttamente la memoria
- Parser.h
    - Libreria che implementa gli elementi necessari per il parsin, come la stream di token e funzioni utili per la verifica di errori sintattici
- Parser.cpp
    - Implementa le funzioni/metodi di parser.h
- Token.h e Token.cpp
    - Definizione dei token, ai quali si assegna un numero al quale corrispondono
    - Token.cpp si occupa dell'overload dell'operatore di stampa
- Tokenizer.h
    - È la libreria che implementa il tokenizer, che si occupa dell'abbinamento file-token_sequence
- Visitor.h
    - È la libreria che implementa il vero e proprio esecutore delle istruzioni, in base a ciò che legge dalla token stream, il visitor esegue le varie operazioni
- Interpreter.cpp 
    - È il programma "main", che si occupa di eseguire in sequenza le fasi di analisi lessicale, semantica e sintattica.

## Giorno 3 - 5/08/2023
Definita la struct token, e l'overload del'operatore di inserimento.
Iniziato a definire i file Tokenizer.h e Tokenizer.cpp

## Giorno 4 e 5 - 09/08/2023
Implementato in maniera completa la parte che si occupa dell'analisi lessicale, dal file di input viene adesso generata una sequenza di tokens con il lessema corrispondente

Creazione di uno "scheletro" per l'analisi lessicale, a partire dall'UML