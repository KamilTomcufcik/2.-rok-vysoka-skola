#ifndef STATION_H
#define STATION_H
// Pocet trati k dispozicii
#define STATION_SIZE 10
// Maximalny pocet znakov pre ulozenie nazvu cielovej stanice
#define TARGET_SIZE 36

/**
 * Jeden zaznam o kapacite do cielovej stanice
 */
struct car {
    // Cielova stanica / nazov
    char value[TARGET_SIZE];
    // Pocet cestujuchich
    int capacity;
    // Smernik na dalsi zaznam
    struct car* next;
};

/**
 * Cela databaza zaznamov
 */
struct station {
    // Dynamicke pole smernikov na zaznamy
    // jeden zaznam ma typ struct car*
    struct car** tracks;
    // Velkost pola tracks
    int track_count;
};


/**
 * Vytvori prazdnu stanicu.
 * Alokuje pole smernikov tracks na pociatocnu kapacitu STATION_SIZE
 * nastavi velkost capacity na STATION_SIZE
 * @return smernik na prazdnu stanicu
 */
struct station* create_station();

/**
 * Uvolni pamat
 * @param smernik na databazu
 */
void destroy_station(struct station* station);

/**
 * Vyberie poziciu v poli station->tracks pre ulozenie zaznamu target
 *
 * Proces vyberu by mal splnat kriteria pre hash funkciu:
 * - rovnaky retazec by mal vzdy mat rovnaky vysledok
 * - pre rozne retazce by mali byt vysledky co najviac rozne
 *
 * @param smernik na databazu
 * @param nazov cielovej stanice
 * @return cislo v intervale 0 az N-1, kde N je  station->track_count
 */
int select_track(struct station* station, const char* target);

/**
 * Zvysi zaznam o pocte cestujucich do danej cielovej stanice.
 *
 * Najprv sa vyberie cielova trat pomocou select_track(). Ak zaznam neexistuje, 
 * vytvori sa novy. Ak zaznam na danej trati (spojkovom zozname) existuje, cislo sa pripocita.
 * V databaze nesmu byt dva zaznamy s rovnakou cielovou stanicou.
 *
 * @param smernik na databazu
 * @param nazov cielovej stanice
 */
void add_target_capacity(struct station* station,const char* target, int capacity);

/**
 * Ziska zaznam o cielovej stanici.
 * @param smernik na databazu
 * @param nazov cielovej stanice
 *
 * @return kapacitu do cielovej stanice. Ak sa zaznam nenachedza, vrati nula.
 */
int get_target_capacity(struct station* station,const char* target);

/**
 * Spocita pocet cielovych stanic
 * @param smernik na databazu
 */
int count_targets(struct station* station);

/**
 * Spocita kapacitu vo vsetkych zaznamoch
 * @param smernik na databazu
 */
int count_capacity(struct station* station);
#endif