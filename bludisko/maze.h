#ifndef _MAZEH
#define _MAZEH

/**
 * Funkcia by mala zobrať vstupnú mriežku a 
 * vyznačiť na nej cestu z ľavého horného rohu do pravého dolného rohu. 
 * Mriežka je uložená do jednorozmerného poľa, pričom najprv ide prvý riadok,
 * za ním druhý a tak ďalej. 
 *
 * Na mriežke sa nachádzajú znaky: 
 * ' ' - voľné miesto
 * 'x' - stena. Stena nesmie byť prepísaná.
 * '*' - poloha potkana. Na začiatku je na 0,0.
 *
 * @param maze Štvorcová mriežka rozmeru size x size.
 * @param size Rozmer mriežky
 * @return 1 ak existuje riešenie, 0 inak.
 */
int solve_maze(char* maze,int size);


#endif
