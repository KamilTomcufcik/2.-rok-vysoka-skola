#ifndef TRAIN_H
#define TRAIN_H
#define SIZE 100

/**
 * Jeden vozen vlaku
 */
struct car {
    /**
     * Nazov cielovej  stanice
     */
    char value[SIZE];
    /**
     * Smenik na dalsi vozen
     */
    struct car* next;
};

/**
 * Prida vozen na koniec vlaku.
 *
 * @arg nazov cielovej stanice, ktory sa ma priradit novemu voznu.
 * @return smernik na zaciatok vlaku.
 */
struct car* add_car(struct car* first,const char* target);


/**
 * Vypise vsetky vozne vo vlaku
 *
 * @arg smernik na prvy vozen
 */
void print_train(struct car* first);

/**
 * Zrusenie vsetkych voznov vo vlaku.
 * @arg smernik na prvy vozen
 */
void cancel_train(struct car* first);

/**
 * Vyradenie vsetkych voznov, ktorych cielova stanica je target
 *
 * @arg smernik na prvy vozen
 * @arg cielova stanica, ktora sa ma vyradit z vlaku.
 * @return smernik na novy prvy vozen
 *
 */
struct car* clear_train(struct car* first,const char* target);

#endif // TRAIN_H
