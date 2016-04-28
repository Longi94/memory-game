#ifndef DRAW_SECONDARY_H_INSERTED
#define DRAW_SECONDARY_H_INSERTED

/*kissebb rajzolasok*/

/**
 * Kitorol mindent a megnyitott ablakban egy egyszeru fekete teglalappal. SDL_Flip()-et nem tartalmaz.
 * @param scr felulet pointer
 */
void clearscreen(SDL_Surface *scr); /*ablakon mindent torol*/

/**
 * Kirajzol szoveget. Fokent a kod roviditesert van. SDL_Flip()-et nem tartalmaz.
 * @param scr felulet pointer
 * @param text szoveget tartalmazo feluletre mutato pointer
 * @param x x koordinata
 * @param y y koordinata
 */
void drawtext(SDL_Surface *scr, SDL_Surface *text, int x, int y);/*szöveg kirajzolása*/

/**
 * Betutipus betoltes sikeressegenek elenorzese. Hibauzenet kiirasa "stderr.txt"-be ha sikertelen volt.
 * @param font betutipus pointer
 */
void fonterrorcheck(TTF_Font *font);

#endif
