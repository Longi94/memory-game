#ifndef GAMEPLAY_H_INSERTED
#define GAMEPLAY_H_INSERTED

/*maga a jatek*/

/**
 * @typedef PlayState
 * A PlayState enumeracio tipus definicioja.
8 */
/**
 * @enum PlayState Egy enum tipus a startnewgame()-ben levo kisseb allapotgepnek a jatek menetenek kezelesere.
 */
typedef enum PlayState {WAIT, /**< Egy kartya kivalsztasara var*/
                        SELECTED /**< Masodik kartya kivalasztasara var*/
                        } PlayState;

/**
 * Az egesz jatek kezelese a gameplayfs-ben levo fuggvenyek segitsegevel.\n
 * Eloszor ellenorzi hogy a felhasznalo az "Uj Jatek" vagy a "Betoltes gombra kattintott es ez alapjan hatarozza meg a beallitasokat.
 * Kiszamolja a szukseges adatokat es kirajzolja a jatek feluletet. Ha a felhasznalo a "Betoltes" gombra kattintott akkor a mar megtalalt
 * paroka felfele forditva rajzolja ki. Lefoglalja a megfelelo meretu memoriat a kartyaknak. Letrehoz egy idozitot ami az ido meresere szolgal.
 * Megkezdodik az SDL esemenyek kezelese. Csak a kattintasokat vezerli, mert mast nem kell. A megtalalt parok detektalasara egy kicsi allapot
 * gepet hasznal. A jatek vegekor torli az idozitot es felszabaditja a korabban lefoglalt memoriat.
 * @param scr felulet pointer
 * @param options a beallitasokat tartalmazo tomb
 * @param clickedmenu pointer a main-ben levo CurrentMenu tipusu "menu" valtozora, a kovetkezo menu megjelenitesenek kezelesere
 * @param toquit pointer a main-ben levo "quit" valtozora, a program bezarasanak kezelesere
 * @param loadsavedgame logikai tipus, hogy a fuggveny eldontse, hogy uj jatekot kezdett a felhasznalo hogy betloltotte egy mentett jatekot
 * @param gamescore a main.c-ben levo valtozora mutato pointer (vissza adja az eredmenyt)
 * @param gametime a main.c-ben levo valtozora mutato pointer (vissza adja az eredmenyt)
 * @param gamediff a main.c-ben levo valtozora mutato pointer (ez alapjan dontjuk el, hogy melyik lancolt listaba kell beszurni az eredmenyt)
 */
void startnewgame(SDL_Surface *scr, int *options, CurrentMenu *clickedmenu, char *toquit, int loadsavedgame, int *gamescore, int *gametime, int *gamediff);

#endif
