#ifndef DRAW_H_INSERTED
#define DRAW_H_INSERTED

#include"fileop.h"
/*rajzolas*/

/**
 * Kirajzolja a fomenut. SDL_Flip()-et tartalmaz.
 * @param scr felulet pointer, ahova rajzol
 */
void drawmainmenu(SDL_Surface *scr);/*fomenu kirajzolasa*/

/**
 * Kirajzolja a beallitasok menut az atvett beallitasok tomb alapjan. SDL_Flip()-et tartalmaz.
 * @param scr felulet pointer, ahova rajzol
 * @param currentopt a beallitasokat tartalmazo tomb
 */
void drawoptionsmenu(SDL_Surface *scr, int *currentopt); /*beallitasok menu kirazolasa*/

/**
 * Kirajzolja a ranglista menut a kapott lancolt listat felhasznalva. A "diff" pointer egy int-re mutat 0 es 1 kozott valtogat amikor a
 * felhasznalo a konnyu es a nehez ranglista kozott valtogat. SDL_Flip()-et tartalmaz.
 * @param scr felulet pointer, ahova rajzol
 * @param scoreslist ranglistat tartalmazo lancolt lista
 * @param diff logikai tipusra mutato pointer
 */
void drawscoresmenu(SDL_Surface *scr, ScoreList *scoreslist, int *diff);/*ranglista menu kirajzolasa*/

/**
 * Kirajzolja a jatek feluletet (felso es also sav) es a bennuk levo szovegeket. SDL_Flip()-et tartalmaz.
 * @param scr felulet pointer, ahova rajzol
 */
void drawnewgame(SDL_Surface *scr); /*Uj jatek ablak megrajzolasa (felso es also sav)*/

/**
 * Kartyakat rajzolja meg egy uj vagy egy betoltott jatok megkezdesekor. Atveszi hogy hany sor, hany oszlop van, mekkora kartyakat kell
 * kirajzolni es, hogy milyen nehezsegen jatszik a jatekos. Egyszeru egymasba agyazott ciklusokat hasznal. SDL_Flip()-et tartalmaz.
 * @param scr felulet pointer, ahova rajzol
 * @param rows sorok szama
 * @param columns oszlopok szama
 * @param cardsize kartya merete
 * @param diff logikai tipus (melyik nehezsegen jatszik)
 */
void drawcards(SDL_Surface *scr, int rows, int columns, int cardsize, int diff);/*kartyak kirajzolasa leforditva*/

/**
 * Egy kartyat rajzol ki. Atveszi hogy hova kell kirajzolni, mekkorat es a kirajzolando fajl nevet. SDL_Flip()-et tartalmaz.
 * @param scr felulet pointer
 * @param xcoord x koordinata
 * @param ycoord y koordinata
 * @param cardsize kartya merete
 * @param filename betoltendo fajl neve
 */
void drawonecard(SDL_Surface *scr, int xcoord, int ycoord, int cardsize, const char *filename);/*egy kartya kirajzolasa*/

/**
 * Frissiti a megtalalt parok szamat, amikor a jatekos megtalal egy part. SDL_Flip()-et nem tartalmaz.
 * @param scr felulet pointer
 * @param foundpairs megtalalt kartyak szama
 */
void redrawfoundpairs (SDL_Surface *scr, int foundpairs);/*megtalalt kartyak szamanak frissitese*/

/**
 * Frissiti az idot. Az idozito ezt masodpercenkent meghivja amikor megy a jatek. SDL_Flip()-et tartalmaz.
 * @param scr felulet pointer
 * @param time ido masodpercben
 */
void redrawtime (SDL_Surface *scr, int time);/* ido frissitese*/

/**
 * Frissiti a pontszamot, amikor a jatekos felfordit 2 kartyat fuggetlenul attol hogy part talalt-e vagy nem. SDL_Flip()-et tartalmaz.
 * @param scr felulet pointer
 * @param score pontszam
 */
void redrawscore (SDL_Surface *scr, int score);/*pontszam frissitese*/

/**
 * A jatek vege kepet rajzolja ki, amikoe a jatekos megnyeri a jatekot. SDL_Flip()-et nem tartalmaz.
 * @param scr felulet pointer
 * @param score pontszam
 * @param time ido masodpercben
 */
void drawwin(SDL_Surface *scr, int score, int time);/*jatek vege kep kirajzlasa*/

#endif
