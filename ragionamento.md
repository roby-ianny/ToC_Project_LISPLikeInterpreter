#Problemino problemone
## Problema
Allora, ragioniamo un attimino, il programma è costituito da un blocco principale, ovvero un vettore di statements.
Questo blocco principale è contenuto in program.

Vi sono degli statement che possono contenere a loro volta dei blocchi, questi statement sono While e If.
Per via di questa dipendenza ciclica statement in block e block in statement, abbiamo fatto in modo che i metodi di allocazione di statement nel vettore sono stati implementati all'interno di program.
Il problema sussiste ora nella fase di parsing. Giunti al parsing di while e if si incombe appunto in questa problematica, cosa succede se incontro "Block"?
L'unica alternativa possibile e quella di fare il parsing di questo block come un'unità intera, il che avrebbe abbastanza senso
Il fatto è che per come ho strutturato recursiveparse io non posso fare il parsing del bloccone perché recursiveparse è un metodo che restituisce uno statement.

## Idea
Senza alterare la struttura attuale si può fare la seguente cosa.
Essendo recursiveparse una struttura ricorsiva, essa gestisce situazioni di elementi di un tipo composti a loro volta da elementi dello stesso tipo, ma ciò non mi vieta di gestire la cosa in maniera sequenziale, verrebbe da dire, ma come?
L'idea è quella che, quando si incontra BLOCK, si effettua un parsing *sequenziale*, statement per statement. Finché non si arriva alla parentesi che chiude quella prima della parola chiave "Block".

Si avrà quindi la famosa "statement_list", il problema però potrebbe essere un altro adesso, come (cazzo) metto un blocco intero in un albero sintattico? 
Tecnicamente la risposta sarebbe: "non ce lo metto, ci infilo semplicemente tutto gli statements che contiene"

E poi?
E poi non me ne frega più niente perché sarà un problema del roberto del futuro quando dovrà fare il ExecutionVisitor.
Ok ma ha senso con la forma dell'albero sintattico? tecnicamente si perchè alla fine tutto ciò è contenuto da uno statement più "grosso", ovvero uno di quelli di cui parlavo prima, if e while)

Infatti, per come il linguaggio è stato definito, non è che block compare a caso, ma solo in determinate situazioni, che sono 3.
1. all'inizio del programma
2. in un if statement se bisogna eseguire più di un'istruzione
3. in un while statement se bisogna eseguire più di un'istruzione

ma allora così tecnicamente siamo tutti più felici, questo perché non bisogna scardinare tutta la struttura attuale, perché si la classe block esiste, ma in realtà ciò che dovrebbe fare è stato suddiviso tra Program (parser) e gli statements.
Di fatti io quando faccio il parsing di block, non restituisco altro che una serie di statements.

## Implementazione (bozza)
```cpp

case Token::BLOCK : 
{
	safe_next(itr);		//passo al prossimo token
	recursiveParse(itr); 	//eseguo il parsing del primo statement della lista
	safe_next(itr)		//ora applico l'idea	
	//se incontro una parentesi chiusa significa che il blocco ha terminato le istruzioni, e quindi ho finito di fare il parsing delle istruzioni
	//se non incontro la parentesi chiusa (oltre a quello dello statement appena elaborato) allora vuol dire che bisogna fare il parsing di altri statements nel blocco	
	if(itr->tag == Token::RP) break;
	else recursiveParse(itr);
}
```
