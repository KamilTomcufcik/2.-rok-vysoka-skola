#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

void pocitanie(float zasobnik[], int counter, char zadane[])
{
  if (zadane[0] == '+')
  {
    zasobnik[counter - 1] = zasobnik[counter - 1] + zasobnik[counter];
  }
  else if (zadane[0] == '-')
  {
    zasobnik[counter - 1] = zasobnik[counter - 1] - zasobnik[counter];
  }
  else if (zadane[0] == '*')
  {
    zasobnik[counter - 1] = zasobnik[counter - 1] * zasobnik[counter];
  }
  else if (zadane[0] == '/')
  {
    if (zasobnik[counter] == 0)
    {
      printf("division by zero\n");
      exit(0);
    }
    zasobnik[counter - 1] = zasobnik[counter - 1] / zasobnik[counter];
  }
}

void vypis(float zasobnik[], int counter)
{
  if (counter == 0) // vypis pre jedno cislo
  {
    printf("%.2f ", zasobnik[0]);
  }
  else
  {
    for (int i = 0; i <= counter; i++) //vypis
    {
      printf("%.2f ", zasobnik[i]);
    }
  }
  printf("\n");
}

int main()
{
  char zadane[SIZE];
  int counter = 0;
  float zasobnik[10];
  char znaky[] = "/*-+";

  while (1)
  {
    if (fgets(zadane, SIZE, stdin) == NULL) //nacitavanie
      break;
    if (zadane[0] == '\n')
    {
      printf("no input\n");
      return 0;
      break;
    }

    if (strpbrk(zadane, znaky) == NULL && !isdigit(zadane[0])) // ak najde znak tak nieje null
    {
      printf("bad input\n");
      return 0;
    }
    if (zadane[0] > 47) // ak to je cislo
    {
      zasobnik[counter] = atof(zadane);
      vypis(zasobnik, counter);
      counter++;
    }
    else if (zadane[0] < 48 && counter > 1) //ak to je operand a mam dost cisel
    {
      counter--;
      // vypis(zasobnik, counter);
      pocitanie(zasobnik, counter, zadane);
      counter--;
      vypis(zasobnik, counter); // do vypisu davam o counter menej ale iba tu
      counter++;
    }
    else if (zadane[0] < 48 && counter < 2) // print malo cisel a operand
    {
      printf("not enough operands\n");
      return 0;
    }
    if (counter == 10) //print plny zasobnik
    {
      printf("full stack\n");
      return 0;
    }
  }

  printf("no input\n");

  return 0;
}