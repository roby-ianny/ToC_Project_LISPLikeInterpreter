#ifndef STMT_MGR_H
#define STMT_MGR_H

#include <vector>

#include "Statement.h"

//gestore dei nodi per la deallocazione
class StatementManager{
    StatementManager() = default;
    ~StatementManager(){
        clearMemory();  //funzione che definisco per la deallocazione
    }

    //Elimino copia e assegnamento per evitare deallocazioni multiple
    StatementManager(const StatementManager& other) = delete;
    StatementManager& operator=(const StatementManager& other) = delete;

    //Utilizzo il pattern factory method per creare gli oggeti expression
    

    void clearMemory(){
        //code
    }
};


#endif