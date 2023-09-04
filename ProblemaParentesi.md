# Problema

Di per sè l'interprete a grandi linee funziona
Il problema è che il parser ha problemi con le parentesi che risultano non corrispondenti in caso di IF contenenti altri IF, o IF contenenti altri blocchi.

Bisogna quindi rivedere l'avanzamento dell'iteratore durante il parsing di elementi con condizioni come IF e while.
Ovvero bisogna rivedere la struttura generale nel caso in cui ci siano degli statement che contengono dei blocchi.