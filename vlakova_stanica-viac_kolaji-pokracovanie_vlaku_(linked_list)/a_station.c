#include "a_station.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct station *create_station()
{
  struct station *station = (struct station *)calloc(1, sizeof(struct station));
  station->tracks = (struct car **)calloc(STATION_SIZE, sizeof(struct car *));
  station->track_count = STATION_SIZE;
  return station;
}

void destroy_station(struct station *station)
{
  for (int i = 0; i < STATION_SIZE; i++)  //prechadza vsetky tracks
  {
    struct car *ll = station->tracks[i];
    struct car *dalsi;
    while (ll)
    {
      dalsi = ll->next;   // v dalsom je nasledujuci vlak
      free(ll);           // clearnem prvy
      ll = dalsi;         // do ll ulozim dalsi
    }
  }
}

int select_track(struct station *station, const char *target)
{
  unsigned long hash = 5381;  // djb2 hashovacia funkcia z netu
  int c;
  while ((c = *target++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % STATION_SIZE;   // upravim vysledne cislo z funkcie aby som dostal polohu v nasom specifickom poli
}

void add_target_capacity(struct station *station, const char *target, int capacity)
{
  int kolaj = select_track(station, target);    // dostanem specificku kolaj
  if (station->tracks[kolaj] == NULL)           // ak je prazdna tak ulozim hodnotu
  {
    station->tracks[kolaj] = calloc(1, sizeof(struct car));
    strcpy(station->tracks[kolaj]->value, target);
    station->tracks[kolaj]->capacity = capacity;
    return;
  }
  struct car *ll = station->tracks[kolaj];
  while (ll)                // ak nie je prva hodnota prazdna
  {
    if (strcmp(ll->value, target) == 0)   // porovnam nazov, ak sa rovna pripocitam capacity
    {
      ll->capacity += capacity;
      return;
    }
    if (ll->next == NULL)           // ak je next null tak to ulozim tam, returny mi zabezpecuju ze nebudem mat viacej zaznamov
    {
      struct car *novyVozen = calloc(1, sizeof(struct car));
      strcpy(novyVozen->value, target);
      novyVozen->capacity = capacity;
      ll->next = novyVozen;
      return;
    }
    ll = ll->next;
  }
}

int get_target_capacity(struct station *station, const char *target)
{
  int kolaj = select_track(station, target);
  struct car *ll = station->tracks[kolaj];
  while (ll)   // ak ll nie je null tak sa porovna ci sa target rovna value, potom sa vrati capacity
  {
    if (strcmp(ll->value, target) == 0)
    {
      return ll->capacity;
    }
    ll = ll->next;
  }
  return 0;     // ak sme presli ll a nenasli sme target tak vratime 0
}

int count_targets(struct station *station)
{
  int counter = 0;
  for (int i = 0; i < STATION_SIZE; i++) // prechazda vsetky tracks
  {
    struct car *ll = station->tracks[i];
    while (ll)        // prechadza ll
    {
      counter++;
      ll = ll->next;
    }
  }
  return counter;
}

int count_capacity(struct station *station)
{
  int counter = 0;
  for (int i = 0; i < STATION_SIZE; i++)      // to iste co je hore
  {
    struct car *ll = station->tracks[i];
    while (ll)
    {
      counter += ll->capacity;
      ll = ll->next;
    }
  }
  return counter;
}