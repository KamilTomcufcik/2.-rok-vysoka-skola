Tomčufčík Kamil                                                                     27.01.2022
                                    KOMPRESOR/DEKOMPRESOR                                           

Zadanie
Kompresor a dekompresor by mal byť schopný pracovať s ľubovoľným binárnym súborom do 10 MB.
Súbor by mal byť po skomprimovaní menší minimálne o 10 percent a po dekomprimovaní by mal byť
zhodný s pôvodným súborom.

Stručný opis funkčnosti
kompilácia programu:
make all
spustenie programu:
kompresia -> ./program -c infile outfile
dekompresia -> ./program -d infile outfile

Podmienky za ktorých program funguje
kompresia funguje iba v prípade, že vstupný súbor má viac ako 1 unikátnych znakov
dekompresia funguje iba v prípade, že vstupný súbor má na začiatku uložený Huffmanov strom


Stručný opis riešenia
kompresia:
Pri kompresii program nájde všetky unikátne znaky a ich frekventovanosť (počet)
následne vytvorí binárny strom pomocou huffmanovho kódovania, potom sa kódy, ktoré získame
prechodom binárneho stromu, uložia do "mapy", ktorá sa najprv uloží do outfile a potom sa 
použije na zmenu znakov na string bitov, ktorý sa na koniec zmení naspäť na znaky a zapíše
do súboru.

dekompresia:
Pri dekompresii si program najprv nájde unikátne znaky a ich kódy, z ktorých si postupne 
vytvára binárny strom, následne sa načítavajú znaky, ktoré sa potom premieňajú na string
bitov, ktorý potom program využíva na prechádzanie stromom. Ak narazí na list tak zapíše
znak, ktorý je zapísaný v liste do premennej, ktorú neskôr program zapíše do outfile


Z tretieho zdroja som zobral kód na vytvorenie stromu. Tento kód som ale trochu upravoval
na základe mojich potrieb. Ostatné zdroje boli iba inšpiráciou alebo dokumentáciou 
(nie úplne dokumentácia, ale pomohli mi pri pochopení niektorých konceptov).

Zdroje:
https://www.geeksforgeeks.org/huffman-decoding/
https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
https://www.geeksforgeeks.org/efficient-huffman-coding-for-sorted-input-greedy-algo-4/
https://www2.cs.duke.edu/csed/poop/huff/info/
https://www.programiz.com/dsa/huffman-coding
https://www.geeksforgeeks.org/pre-increment-and-post-increment-in-c/
https://www.cplusplus.com/reference/cstring/strcat/
https://www.asciitable.com/