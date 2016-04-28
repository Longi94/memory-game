/**
 * @file draw_secondary.c
 * @brief Kisebb rajzolasi fuggvenyek.
 *
 * Fokent azert vannak a fuggvenyek hogy a kodot atlathatobba, egyszerubbe es rovidebbe tegye.
 */

#include<SDL.h>
#include<SDL_gfxPrimitives.h>
#include<SDL_ttf.h>
#include"draw_secondary.h"

void clearscreen(SDL_Surface *scr)
{
    boxRGBA(scr, 0, 0, scr->w, scr->h, 0, 0, 0, 255);
}

void drawtext(SDL_Surface *scr, SDL_Surface *text, int x, int y)
{
    SDL_Rect textcoord = {0,0,0,0};
    textcoord.x = x;
    textcoord.y = y;
    SDL_BlitSurface(text, NULL, scr, &textcoord);
    SDL_FreeSurface(text);
}

void fonterrorcheck(TTF_Font *font)
{
    if (!font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        exit(1);
    }
}

