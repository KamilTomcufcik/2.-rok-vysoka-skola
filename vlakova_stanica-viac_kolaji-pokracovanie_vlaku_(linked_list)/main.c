#include "a_station.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void print_station(struct station *station)
{
  // Vypise celu stanicu
  printf("\nstation>>>  ");
  // Prechadza vsetky trate
  for (int i = 0; i < station->track_count; i++)
  {
    struct car *start = station->tracks[i];
    struct car *this = start;
    // Prechadza vsetky vozne
    while (this != NULL)
    {
      printf("%s %d -> ", this->value, this->capacity);
      this = this->next;
    }
    printf("NULL  ");
  }
  printf("<<<station\n\n");
}
// Pre overenie ci to ide v poriadku
void test_station(struct station *station)
{
  const char *stations[] = {"Presov", "Kosice", "Banska Bystrica", "Banska Stiavnica", "Povazska Bystrica", "Snina", "Humenne", "Bratislava", "Pezinok", "Skalica", "Ruzomberok", "Bidovce", "Michalovce", "Poprad", "Krompachy", "Smizany", "Vajkovce", "Budimir", "Modra", "Myslava", "Roznava", "Gemerska Poloma", "Stratena", "Dobsina", "Michalany", "Kostolany"};
  int size = 26;
  for (int i = 0; i < 10; i++)
  {
    int s = rand() % size;
    int c = rand() % 20;
    printf("%s %d", stations[s], c);
    add_target_capacity(station, stations[s], c);
    print_station(station);
  }
}

int main()
{
  srand(time(NULL));
  struct station *station = create_station();
  test_station(station);
  printf("%d  %d  %d\n", get_target_capacity(station, "Presov"), count_targets(station), count_capacity(station));
  // print_station(station);
  // printf("%d\n", select_track(station, "Presov"));
  // printf("%d\n", select_track(station, "Kosice"));
  destroy_station(station);
  return 0;
}
