#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

struct pizza
{
  float price;
  char meno[SIZE];
  char odmeno[SIZE];
};

void vymena(char zadane[]) //uprava zadaneho riadka na jednoduchsie vyhladavanie
{
  char numbers[] = "0123456789";
  char letters[] = "oizeasbtbq";
  for (int i = 0; i < strlen(zadane); i++)
  {
    if (zadane[i] > 47 && zadane[i] < 58)
    {
      for (int j = 0; j < 10; j++)
      {
        if (zadane[i] == numbers[j])
          zadane[i] = letters[j];
      }
    }
    if (zadane[i] > 64 && zadane[i] < 91)
      zadane[i] = tolower(zadane[i]);
  }
}

void search(const int counter, const char filter[], struct pizza listok[])
{
  int f = strlen(filter);
  int k = 0;
  for (int i = 0; i < counter; i++) // for na array
  {
    // printf("loop i %i\n", i);
    for (int j = 0; j < strlen(listok[i].odmeno) - f; j++) //for na slovo
    {
      // printf("loop j %li\n", strlen(listok[i]));
      if (f > strlen(listok[i].odmeno))
        break;
      if (listok[i].odmeno[j] == filter[0])
      {
        for (k = 0; k < f - 1; k++)
        {
          // printf("loop k%i  %i  %c  %c  %c\n", k, f, filter[k], listok[i][j + k], listok[i][j + k] - 32);
          if (filter[k] != listok[i].odmeno[j + k])
          {
            break;
          }
        }
        if (k == f - 1)
        {
          printf("%s%.2f\n", listok[i].meno, listok[i].price);
          break;
        }
      }
    }
  }
}

int main()
{
  char zadane[SIZE], filter[SIZE];
  int counter = 0, pomocna = 0;
  struct pizza listok[30];

  fgets(zadane, SIZE, stdin); //  nacitanie filtra
  vymena(zadane);
  strcpy(filter, zadane);

  while (1)
  {
    if (fgets(zadane, SIZE, stdin) == NULL) //nacitavanie listka
      break;
    if (zadane[0] == '\n')
      break;

    if (pomocna == 0) // ukladanie listka do array-u
    {
      strcpy(listok[counter].meno, zadane);
      vymena(zadane);
      strcpy(listok[counter].odmeno, zadane);
      pomocna = 1;
    }
    else if (pomocna == 1)
    {
      listok[counter].price = atof(zadane);
      counter++;
      pomocna = 0;
    }
  }

  // finalny vypis
  printf("Zadaj hladanu surovinu:\n");
  printf("Zadaj jedalny listok:\n");
  search(counter, filter, listok);
  printf("Nacitanych %i poloziek.\n", counter);

  return 0;
}
