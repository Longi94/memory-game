#ifndef WAITCLICK_H_INSERTED
#define WAITCLICK_H_INSERTED

/*esemenykezeles*/
/**
 * @typedef CurrentMenu
 * A CurrentMenu enumeracio tipusdefinicioja.
 */
/**
 * @enum CurrentMenu
 * Egy enum tipus a megjelenitendo menu kezelesere
 */
typedef enum CurrentMenu {MAIN, /**<Fomenu*/
                          OPTIONS, /**<Beallitasok*/
                          SCORES, /**<Ranglista*/
                          NEWGAME, /**<Uj jatek*/
                          LOADGAME, /**<Betoltes*/
                          WIN /**<Jatek vege*/
                          }
                          CurrentMenu;

/**
 * A fomenuben torteno esemenyeket kezeli. Itt csak a kattintast figyeli es az alapjan, hogy hova kattintott lekezeli azt.
 * @param scr felulet pointer
 * @param toquit pointer a main-ben levo "quit" valtozora, a program bezarasanak kezelesere
 * @param clickedmenu pointer a main-ben levo CurrentMenu tipusu "menu" valtozora, a kovetkezo menu megjelenitesenek kezelesere
 */
void waitclickmainmenu(SDL_Surface *scr, char *toquit, CurrentMenu *clickedmenu); /*kattintas erzekelese a fomenuben*/

/**
 * A beallitasok menuben torteno esemenyeket kezeli, hatasukra megvaltoztatja a beallitsokat. Itt csak a kattintast figyeli es az
 * alapjan, hogy hova kattintott lekezeli azt.
 * @param scr felulet pointer
 * @param toquit pointer a main-ben levo "quit" valtozora, a program bezarasanak kezelesere
 * @param clickedmenu pointer a main-ben levo CurrentMenu tipusu "menu" valtozora, a kovetkezo menu megjelenitesenek kezelesere
 * @param currentopt a beallitasokat tartalmazo tomb
 */
void waitclickoptionsmenu(SDL_Surface *scr, char *toquit, CurrentMenu *clickedmenu, int *currentopt);/*beallitasok mukodese*/

/**
 * A ranglista menuben torteno esemenyeket kezeli. A vissza lepest es a ranglista valtast kezeli.
 * @param scr felulet pointer
 * @param toquit pointer a main-ben levo "quit" valtozora, a program bezarasanak kezelesere
 * @param clickedmenu pointer a main-ben levo CurrentMenu tipusu "menu" valtozora, a kovetkezo menu megjelenitesenek kezelesere
 * @param diff a megjelenitando ranglistat meghatarozo logikai valtozo (konnyu vagy nehez)
 */
void waitclickscoressmenu(SDL_Surface *scr, char *toquit, CurrentMenu *clickedmenu, int *diff);/*ranglista menu mukodese*/

/**
 * A jatek vegekor menuben torteno esemenyeket kezeli. Kattintasra vagy gomb lenyomasra var a tovabb lepeshaz.
 * @param scr felulet pointer
 * @param toquit pointer a main-ben levo "quit" valtozora, a program bezarasanak kezelesere
 * @param clickedmenu pointer a main-ben levo CurrentMenu tipusu "menu" valtozora, a kovetkezo menu megjelenitesenek kezelesere
 */
void waitclickwin(SDL_Surface *scr, char *toquit, CurrentMenu *clickedmenu);

#endif
