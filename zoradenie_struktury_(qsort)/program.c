#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

struct pizza
{
  float price;
  char meno[SIZE];
};

int compare(const void *a, const void *b) //compare funkcia do qsortu
{
  const struct pizza *sa = a, *sb = b;
  if ((sa->price - sb->price) == 0)
  {
    return strcmp(sa->meno, sb->meno);
  }
  return (sa->price > sb->price) - (sa->price < sb->price); //najprv porovna a potom odcitava, hodnoty z porovnavania 1 a 0
}

int main()
{
  char zadane[SIZE];
  int counter = 0, pomocna = 0;
  struct pizza listok[30];

  while (1)
  {
    if (fgets(zadane, SIZE, stdin) == NULL) //nacitavanie listka
      break;
    if (zadane[0] == '\n')
      break;

    if (pomocna == 0) // ukladanie listka do array-u
    {
      strcpy(listok[counter].meno, zadane);
      pomocna = 1;
    }
    else if (pomocna == 1)
    {
      if (zadane[0] > 64)
        break;
      listok[counter].price = atof(zadane);
      counter++;
      pomocna = 0;
    }
  }

  qsort(listok, counter, sizeof(struct pizza), compare);

  for (int i = 0; i < counter; i++) //finalny vypis
    printf("%s%.6f\n", listok[i].meno, listok[i].price);

  return 0;
}
