#ifndef GAMEPLAYFS_H_INSERTED
#define GAMEPLAYFS_H_INSERTED

/*jatekot kezelo fuggvenyek*/
/**
 * @typedef CardProp
 * A CardProp struktura tipusdefinicioja.
 */
/**
 * @struct CardProp
 * @brief Struktura a kartya tulajdonsagainak tarolasara.
 */
typedef struct CardProp {
                        int cindex, /**< A kartya indexe, ez hatarozza meg hogy melyik kepet toltse be, es ezek hatarozzak meg a parokat.*/
                        flipped; /**< Logikai tipus. A kartya fel van-e forditva*/
                        } CardProp;

/**
 * Megfelelo meretu 2 dimenzios dinamikus tombot allokal a kartyaknak.
 * @param rows sorok szama
 * @param columns oszlopok szama
 * @return Az allokalt memoriara mutato pointer adja vissza
 */
CardProp **alloc_dyn_2darray(int rows, int columns);/*2d-s tomb lefoglalasa structtal, visszater pointerrel*/

/**
 * Az allokalt 2 dimenzios tombot szabaditja fel.
 * @param ptrarray a dinamikus pointerre mutato pointer
 */
void free_dyn_2darray(CardProp **ptrarray);/*lefoglalt memoria terolet felszabaditas*/

/**
 * Veletlenszeruen feltolti a 2 dimenzios dinamikus tombot szamparokkal. A tombot linearisan kezeli. General a veletlen szamot 1 es az ures
 * helyek szama kozott. Meg keresi az annyiadik ures helyet es oda masolja be a szamot. A bemasolando szam minden masodik masolas utan no eggyel.
 * @param cardarray a feltoltendo tomb
 * @param rows sorok szama
 * @param columns oszlopok szama
 */
void generate_random_pairs(CardProp *cardarray, int rows, int columns);/*arok randomizalassa*/

/**
 * Meghatarozza hogy milyen nagynak kell lennie a kartyanak hogy kihasznalja az ablak meretet.
 * @param rows sorok szama
 * @param columns oszlopok szama
 * @param windowh az ablak magassaga
 * @param windoww az ablak szelessege
 * @return A negyzet alaku kartyanak az oldalhossza
 */
int deter_cardsize(int rows, int columns, int windowh, int windoww);/*kártyák mretének meghatározása*/

/**
 * Meghatarozza, hogy a kivalasztott kartya hanyadik sorban van
 * @param rows sorok szama
 * @param windowh ablak magassaga
 * @param cardsize a kartya merete
 * @param clickedy y koordinata
 * @return a sor sorszama, -1 ha nem katyara kattintott
 */
int deter_clickedcard_row(int rows, int windowh, int cardsize, int clickedy);/*meghatarozza hogy nayadik sorra kattintott*/

/**
 * Meghatarozza, hogy a kivalasztott kartya hanyadik sorban van.
 * @param columns oszlopok szama
 * @param windoww ablak szelessege
 * @param cardsize a kartya merete
 * @param clickedx x koordinata
 * @return az oszlop sorszama, -1 ha nem kartyara kattintott
 */
int deter_clickedcard_column(int columns, int windoww, int cardsize, int clickedx);/*meghatarozza hogy hanyadik oszlopra kattintott*/

/**
 * A "timer" idozitohoz tartozo fuggveny. SDL_USEREVENT tipusu esemenyt hozz letre meghivaskor.
 * @param ms millisec
 * @param param szabad pointer
 * @return mennyi ido mulva hivodjon meg ujra
 */
Uint32 gametimer(Uint32 ms, void *param);

/**
 * Elmenti a jatekot fajlba.
 * @param rows sorok szama
 * @param columns oszlopok szama
 * @param difficulty nehezseg
 * @param score pontszam
 * @param time ido
 * @param pairsfound megtalalt parok szama
 * @param cards kartyak tulajdonsagait tartalmaz tomber mutato pointerre mutato pointer
 */
void savegame(int rows, int columns, int difficulty, int score, int time, int pairsfound, CardProp **cards);/*jatek mentese*/

/**
 * Betolti a mentett jatek beallitasait.
 * @param rows a sorok szamara mutato pointer
 * @param columns az oszlopok szamara mutato pointer
 * @param difficulty a nehezseg
 * @param score pontszamra mutato pointer
 * @param time idore mutato pointer
 * @param pairsfound a megtalalt parok szamara mutato pointer
 */
void loadgamedata(int *rows, int *columns, int *difficulty, int *score, int *time, int *pairsfound);/*jatek betoltese*/

/**
 * Betolti a a mentett jatek allasat (mit talalt mar meg a jatekos es mit nem).
 * @param rows sorok szama
 * @param columns oszlopok szam
 * @param cards a kartyak tombjere mutato pointerre mutato pointer
 */
void loadgamestate(int rows, int columns, CardProp **cards);

/**
 * Kirajzolja a mar megtalalt parokat mentett jatek betoltesekor.
 * @param scr felulet pointer
 * @param rows sorok szama
 * @param columns oszlopoks szama
 * @param cards kartyak tombjere mutato pointerre mutato pointer
 * @param spacec a kartyaktol balra levo ures hely szelessege
 * @param spacer a kartyak folott leve ures hely magassaga
 * @param cardsize a kartya merete
 * @param diff a nehezseg
 */
void drawfoundpairs(SDL_Surface *scr, int rows, int columns, CardProp **cards, int spacec, int spacer, int cardsize, int diff);

#endif
