Petcu Eduard

=============================

	Task 1

Functia c1() rezolva taskul 1; aceasta apeleasa subprogramul "exec_adancime".
Functia exec_adancime preia tabla de joc din pozitia initiala, numarul de 
"\t" (taburi) care trebuie date si caracterul de inserat 
(care poate fi X sau O). Se verifica daca jocul este finalizat in functia
"joc_terminat" care returneaza 1 si 0 cand jocul este incheiat sau respectiv 
neincheiat. Functia printMatrix afiseaza 
tabla de joc de la momentul apelarii.

=============================

	Task 2

Functia c2() rezolva taskul 2; aceasta apeleaza subprogramul
"exec_adancime_modificat" (similar cu subprogramul de la taskul 1).
Aceasta functie primeste ca parametri starea actuala a jocului, inaltimea,
caracterul corespunzator jucatorului care trebuie sa faca mutarea si 
caracterul corespunzator jucatorului care ne intereseaza sa castige.
Am creat o functie care verifica daca jocul este castigat caz in care
se opreste fortat functia si se marcheaza cu 1 (T) valoarea tablei 
respective.
In caz contraar, se verifica daca jocul este terminat si continua generarea
urmatoarelor tabele de joc. Fiecare joc are valoarea initiala 0 (F) si poate 
deveni 1 (T) daca:
1. Jucatorul care trebuie sa mute este acelasi cu jucatorul care ne
intereseaza sa castige si se gaseste o tabla de joc in lista de copii
in care acesta castiga (se face sau intre toate valorile tablelor de joc
ale copiilor).
2. Jucatorul care trebuie sa mute este diferit de cel care ne intereseaza
sa castige si toate tablele de joc din lista de copii au valoarea 1 (T). 
La final se afiseaza arborele si_sau.
		
=============================

	Task 3

Functia c3() rezolva taskul 3; Am creat o noua structura de data de tip
arbore in care retin pentru fiecare nod numarul de fii si valoare acestuia.
Pentru a retine informatiile citite din fisier am folosit o coada de arbori.
Am citit m perechi de tipul char1-int-char2-char3 unde char1 si char 2 sunt
parantezele, char3 este spatiul sau '\n' iar m reprezinta suma numarului de
noduri de pe linia anterioara citita (considerand m=1 pentru prima linie).
Cand se citeste un numar k intre paranteze deschise se aloca memorie pentru
k fii si se insereaza fiecare din acestia in coada. Cand k se citeste intre
paranteze inchise, i se asigneaza nodului scos din coada valoarea k. Astfel,
se creaza structura arborelui minimax, unde cunoastem valorile tuturor
frunzelor. Algoritmul de minimax este implementat folosind 2 functii care
se apeleaza reciproc recursiv. Functia maximum returneaza valoarea maxima
a fiilor unui nod iar functia minimum returneaza valoarea minima a fiilor
unui nod.

=============================

Timp de lucru total: 14 ore
