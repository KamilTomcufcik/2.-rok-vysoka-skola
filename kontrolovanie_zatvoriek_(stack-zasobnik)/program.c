#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 100

struct stack
{
  char zadane[SIZE];
  int size;
};

void add(struct stack *zasobnik, char c)
{
  if (c == '<' || c == '[' || c == '{')   // zmena otvaracich na zatvaracie
  {
    c += 2;
  }
  else
  {
    c++;
  }
  zasobnik->zadane[zasobnik->size] = c;   // pridanie znaku na koniec
  zasobnik->size += 1;      // pripocita velkost pola
}

void rem(struct stack *zasobnik)
{
  zasobnik->zadane[zasobnik->size - 1] = '\0';    // posledny znak vymaze
  zasobnik->size -= 1;          // odpocita velkost
}

int main()
{
  char zadane[SIZE];
  char zatvorky1[] = "{[<(";    // otvaracie zatvorky
  char zatvorky2[] = "}]>)";    // zatvaracie zatvorky
  char pomocna[2];              // pomocny string na porovnavanie
  struct stack *zasobnik = calloc(1, sizeof(struct stack));

  fgets(zadane, SIZE, stdin);     // nacitanie

  for (int i = 0; i < strlen(zadane); i++)
  {
    pomocna[0] = zadane[i];       // vytvorenie stringu na porovnanie
    pomocna[1] = '\0';
    if (strpbrk(zatvorky1, pomocna))    // ak najde otvaraciu zatvorku
    {
      add(zasobnik, zadane[i]);
    }
    else if (strpbrk(zatvorky2, pomocna)) // ak najde zatvaraciu zatvorku
    {
      if (zasobnik->size == 0)    // a zasobnik je prazdny
      {
        printf("Read: %s", zadane);
        printf("Unexpected closing bracket %c in %d\n", zadane[i], i);
        free(zasobnik);
        return 0;
      }
      if (zasobnik->zadane[zasobnik->size - 1] == zadane[i])  // a nasiel spravnu zatvaraciu zatvorku
      {
        rem(zasobnik);
      }
      else if (zasobnik->zadane[zasobnik->size - 1] != zadane[i]) // a nenasiel som spravnu zatvaraciu zatvorku
      {
        printf("Read: %s", zadane);
        printf("Crossed bracket %c in %d, expected %c \n", zadane[i], i, zasobnik->zadane[zasobnik->size - 1]);
        free(zasobnik);
        return 0;
      }
    }
  }

  if (zasobnik->size == 0) // ak som presiel cely text a v zadanei nic nie je
  {
    printf("Read: %s", zadane);
    printf("All brackets OK\n");
    free(zasobnik);
  }
  else                      // ak som presiel cely text a ostali mi otvaracie zatvorky
  {
    printf("Read: %s", zadane);
    printf("Missing closing brackets: ");
    for (int i = zasobnik->size - 1; i >= 0; i--)
    {
      printf("%c", zasobnik->zadane[i]);
    }
    printf("\n");
    free(zasobnik);
  }

  return 0;
}