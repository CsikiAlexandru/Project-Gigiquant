# Analiză Algoritmică a Datelor Financiare

Acest proiect este o aplicație scrisă în limbajul C, dezvoltată pentru a procesa și analiza seturi de date financiare (valori ale acțiunilor, randamente, probabilități). Programul este împărțit în patru task-uri (cerințe) distincte, fiecare utilizând structuri de date specifice pentru optimizarea calculelor.

# Descrierea Task-urilor

1. **Task 1 (Indicatori Financiari):** Calculează randamentul mediu, volatilitatea și indicele Sharpe (Sharpe Ratio) pe baza unui set de valori, utilizând **liste înlănțuite**.
2. **Task 2 (Analiza Discrepanțelor):** Compară valorile din 3 orașe/piețe diferite folosind **stive** și identifică anomaliile (când două valori coincid, iar a treia diferă), salvând rezultatele într-o **coadă** pentru afișare.
3. **Task 3 (Clasificarea Acțiunilor):** Folosește un **arbore binar** pentru a clasifica și grupa evoluția acțiunilor în funcție de fluctuațiile lor de preț pe parcursul mai multor zile.
4. **Task 4 (Probabilități - Lanțuri Markov):** Modelează tranzițiile de preț sub forma unui **graf orientat** (cu probabilități calculate prin fracții ireductibile) pentru a determina șansa ca o acțiune să atingă un prag țintă (Target) după `k` pași.

# Structura Proiectului

Codul sursă este modularizat pentru a fi ușor de citit și extins:

* `tema.c` - Punctul de intrare în program (conține funcția `main`). Aici se face selecția task-ului în funcție de numele fișierului de intrare (`data1.in` - `data20.in`).
* `functii.h` / `functii.c` - Definițiile structurilor (noduri, stive, cozi) și implementarea logicii pentru **Task 1** și **Task 2**.
* `functii_task3.h` / `functii_task3.c` - Implementarea arborilor binari și a logicii de parcurgere/clasificare pentru **Task 3**.
* `functii_task4.h` / `functii_task4.c` - Implementarea grafului, algoritmului de simplificare a fracțiilor și înmulțirii matricelor de adiacență pentru **Task 4**.

# Compilare și Rulare

Pentru a compila programul, ai nevoie de un compilator C (ex: `gcc`). Deoarece proiectul utilizează funcții din biblioteca matematică (`<math.h>`, precum `sqrt` sau `pow`), compilarea trebuie făcută incluzând flag-ul `-lm`.
