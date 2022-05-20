Tomčufčík Kamil                                                                     27.01.2022
                                          MAZE                                           

Zadanie
Úlohou je modifikovať dané pole 'maze' tak, aby v ňom bola na konci programu vyznačená cesta
vonku z bludiska.

Stručný opis funkčnosti
kompilácia programu:
make all
spustenie programu:
príkaz na spustenie -> ./program

Podmienky za ktorých program funguje
bludisko musí mať optimálnu cestu vytvorenú tak, aby sa potkan nemusel pohnúť hore.


Stručný opis riešenia
V default móde si potkan na každom políčku skontroluje pohyb v takomto poradí: východ, juh, 
západ. Ak sa nemá kam pohnúť tak sa zapne mód na vrátenie. Potkan sa vracia na políčka, 
ktoré ma uložené, takže vždy vie kam sa má vrátiť. Na každom políčku skontroluje, či sa nevie 
pohnúť do inej strany, než z ktorej prišiel. Ak nájde inú cestu, pohne sa na jej začiatok 
a prepne sa mód naspäť na default, aby mohol pokračovať pri hľadaní cesty. Ak sa vráti
na štartovné políčko z juhu, tak program vie, že potkan cestu nenašiel a program ukončí.


Zdroje slúžili iba na inšpiráciu.

Zdroje:
https://www.geeksforgeeks.org/rat-in-a-maze-backtracking-2/
https://www.geeksforgeeks.org/count-number-ways-reach-destination-maze/