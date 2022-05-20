#include "a_train.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car *add_car(struct car *first, const char *target)
{
  struct car *novyVozen = calloc(1, sizeof(struct car));  //dynamicke alokovanie pamate
  strcpy(novyVozen->value, target);
  if (first == NULL)      // ak je prazdny list
  {
    return novyVozen;
  }
  struct car *posledny = first;
  while (posledny->next)    // idem na koniec listu
  {
    posledny = posledny->next;
  }
  posledny->next = novyVozen;
  return first;
}

void print_train(struct car *first)
{
  struct car *vozen = first;
  while (vozen)
  {
    printf("%s\n", vozen->value);
    vozen = vozen->next;
  }
}

void cancel_train(struct car *first)
{
  struct car *dalsi;
  while (first)
  {
    dalsi = first->next;  //v dalsom je nasledujuci vlak
    first->next = NULL;   //vymazem pointer 
    free(first);          //clearnem value
    first = dalsi;        //do first dam nasledujuci vlak
  }
}

struct car *clear_train(struct car *first, const char *target)
{
  if (first == NULL)  // ake je prazdny list
  {
    return first;
  }
  if (first->next == NULL && strcmp(first->value, target) == 0) // jeden prvok v liste
  {
    free(first);
    return NULL;
  }
  else if (first->next != NULL && strcmp(first->value, target) == 0)  // viacej prvkov v liste ale hned prvy je ten co hladame
  {
    struct car *temp = first->next;
    free(first);
    return temp;                              //vraciam druhy prvok ako zaciatok listu
  }
  struct car *temp = first;
  while (temp)                                  // prechadzam cely list a hladam dane slovo
  {
    if (temp->next == NULL)               //ak nemam dalsi vlak v liste, podmienka pridana kvoli posllednemu riadku vo while
      break;

    struct car *second = temp->next;      // druhy vlak

    if (strcmp(second->value, target) == 0)     //ak sa druhy vlak rovna slovu
    {
      struct car *third = second->next;     // treti vlak
      temp->next = third;                 //do prveho vlaku ukladam smernik na treti vlak
      free(second);                       //vymazanie druheho vlaku
    }
    temp = temp->next;                  //posuvanie v liste
  }
  return first;
}
