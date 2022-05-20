#include <stdio.h>
#include <string.h>
#include "maze.h"
#include <assert.h>

int solve_maze(char *maze, int size)
{
  int counter = 0;                // pocet krokov
  int dlzka = size * size;        // nechcelo sa mi vsade pisat size*size
  int poloha = 0;                 // aktualny index pola maze 
  int prepinac = 0;               // 0 hladam riesenie, nieco ine = spusti sa  vratenie
  int zoznamPoloh[dlzka];         // zoznam krokov

  while (dlzka != counter)
  {
    while (prepinac != 0)             // while v ktorom riesim vratenie
    {
      poloha = zoznamPoloh[counter - 1];                      // vratim sa na predchadzajuce policko
      counter--;                                              // zmensim counter krokov ktore som spravil
      maze[zoznamPoloh[counter + 1]] = ' ';                   // pole z ktoreho som prisiel zmenim naspat na medzeru
      if (poloha + 1 == zoznamPoloh[counter + 1])             // ked idem spat z prava do lava
      {
        if (maze[poloha + size] == ' ' && poloha + size < dlzka) // ci je dole volne
        {
          poloha += size;
          counter++;
          maze[poloha] = '*';
          prepinac = 0;
          break;
        }
        else if (maze[poloha - 1] == ' ' && poloha % size != 0) // ci je nalavo volne
        {
          poloha--;
          counter++;
          maze[poloha] = '*';
          prepinac = 0;
          break;
        }
      }
      if (poloha + size == zoznamPoloh[counter + 1])         //ked idem spat z dola hore
      {
        if (maze[poloha - 1] == ' ' && poloha % size != 0)            // overujem ci je na lavo volne miesto
        {                                                             // kedze pri pohybe dole uz overujem ci sa mozem pohnut do prava, tak pri vracani sa zdola hore
          poloha--;                                                   // mi staci overit volnost lavej strany
          counter++;                                                  // ak je lava strana volna tak sa tam pohnem, zmenim prepinac a ukoncim loop
          maze[poloha] = '*';
          prepinac = 0;
          break;
        }
      }
      if (poloha == 0)                                              // ak idem spat zprava na start a nenajde mi cestu dole alebo dolava
      {                                                             // alebo ak idem spat zdola hore a nenajde mi cestu dolava
        prepinac = 0;                                               // tento if sa spusti iba v pripade ze pri vracani sa, sa nenasla ina cesta
        return 0;                                                   // ak by sa nasla ina cesta, tak break; by zrusil tento while, a tento if by sa nespustil
      }
    }

    zoznamPoloh[counter] = poloha;

    if (maze[dlzka - 1] == '*')           // overujem ci som na konci bludiska
    {
      break;
    }

    if (maze[poloha + 1] == ' ' && poloha % size != size - 1)   // pohyb doprava
    {
      poloha++;                                                         //kedze maze je jednorozmerne pole tak pohyb doprava sa mi zvacsi index polohy o jedno
      counter++;                                                        // zvacsim counter aby som tuto novu polohu zapisal na dalsie miesto do zoznamu poloh
      maze[poloha] = '*';                                               // na aktualnu polohu dam *
    }
    else if (maze[poloha + size] == ' ' && poloha + size < dlzka) //pohyb dole
    {
      poloha += size;                                                   // pri pohybe dole sa mi index zmeni o size
      counter++;
      maze[poloha] = '*';
    }
    else if (maze[poloha - 1] == ' ' && poloha % size != 0) // pohyb dolava
    {
      poloha--;
      counter++;
      maze[poloha] = '*';
    }
    else                  // nemam sa kde pohnut tak spustim while v ktorom mi funguje  vratenie sa v bludisku
    {
      prepinac = 2;
    }
  }

  return 1;
}
