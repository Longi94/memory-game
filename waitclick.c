/**
 * @file waitclick.c
 * @brief Esemenyeket kezelo fuggvenyek.
 *
 * Ezek a fuggvenyek kezelik nagyreszt az SDL-es esemenyeket.
 */

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "draw_secondary.h"
#include "fileop.h"
#include "waitclick.h"

void waitclickmainmenu(SDL_Surface *scr, char *toquit, CurrentMenu *clickedmenu)
{
    SDL_Event event;
    int click = 0, column1, column2, row1, row2;
    while (!click)
    {
        SDL_WaitEvent(&event);
        column1 = event.button.x < scr->w/2-20 && event.button.x > scr->w/2-280;
        column2 = event.button.x > scr->w/2+20 && event.button.x < scr->w/2+280;
        row1 = event.button.y < 210 && event.button.y > 150;
        row2 = event.button.y < 310 && event.button.y > 250;
        switch(event.type)
        {
            case SDL_QUIT: /*Ha a piros x-re kattint*/
                click = 1;
                *toquit = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT &&
                    event.button.x < scr->w/2+130 && event.button.x > scr->w/2-130 &&
                    event.button.y < 410 && event.button.y > 350) /*Ha a kilepesra kattint*/
                        click = *toquit = 1;
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         column1 && row2) /* Ha a beallitasokra kattint*/
                    {
                        *clickedmenu = OPTIONS;/*valtas beallitasok menure*/
                        click = 1;
                        clearscreen(scr);
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         column1 && row1) /* Ha az Uj jatekra kattint*/
                    {
                        *clickedmenu = NEWGAME;/*Jatek!*/
                        click = 1;
                        clearscreen(scr);
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         column2 && row1 && fexist("save.txt"))/*ha a betoltesre kattint*/
                    {
                        *clickedmenu = LOADGAME;
                        click = 1;
                        clearscreen(scr);
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         column2 && row2) /*Ha a ranglistara kattint*/
                    {
                        *clickedmenu = SCORES;/*Ranglista*/
                        click = 1;
                        clearscreen(scr);
                    }
                break;
        }
    }
}

void waitclickoptionsmenu(SDL_Surface *scr, char *toquit, CurrentMenu *clickedmenu, int *currentopt)
{
    SDL_Event event;
    int click = 0, row1, row2, row3, column1, column2;
    while (!click)
    {
        SDL_WaitEvent(&event);
        row1 = event.button.y > 130 && event.button.y < 150;
        row2 = event.button.y > 180 && event.button.y < 200;
        row3 = event.button.y > 230 && event.button.y < 250;
        column1 = event.button.x > scr->w/2+20 && event.button.x < scr->w/2+40;
        column2 = event.button.x > scr->w/2+250 && event.button.x < scr->w/2+270;
        switch(event.type)
        {
            case SDL_QUIT:
                *toquit = click = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && /*alkalmazas gomb*/
                    event.button.x < scr->w-20 && event.button.x > scr->w-160 &&
                    event.button.y < scr->h-20 && event.button.y > scr->h-70)
                    {
                        *clickedmenu = MAIN;
                        click = 1;
                        clearscreen(scr);
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         column1 && row1) /*felbontas balra lepteto*/
                    {
                        if (*currentopt != 0) (*currentopt)--;
                        clearscreen(scr);
                        click = 1;
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         column2 && row1)/*felbontas jobbra lepteto*/
                    {
                        if (*currentopt != 2) (*currentopt)++;
                        clearscreen(scr);
                        click = 1;
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         column1 && row2)/*nehézség balra lepteto*/
                    {
                        if (currentopt[1] != 0) currentopt[1]--;
                        clearscreen(scr);
                        click = 1;
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         column2 && row2)/*nehezseg jobbra lepteto*/
                    {
                        if (currentopt[1] != 1) currentopt[1]++;
                        clearscreen(scr);
                        click = 1;
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         event.button.x > scr->w/2+20 && event.button.x < scr->w/2+50 &&
                         event.button.y > 275 && event.button.y < 305)/*ranglista torlo pipa*/
                    {
                        currentopt[4] = currentopt[4] ? 0 : 1;
                        clearscreen(scr);
                        click = 1;
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         row3 && column2)/*kartyaszam jobbra lepteto*/
                    {
                        if (currentopt[2] != 10 || currentopt[3] != 10)/*azer ilyen hogy a kartyak szama mindig paros legyen*/
                        {
                            if (currentopt[2] + 2 == currentopt[3])
                            {
                                currentopt[3]--; currentopt[2]++;
                                if (currentopt[2] * currentopt[3] % 2) currentopt[3]++;
                            }
                            else
                            {
                                currentopt[3]++;
                                if (currentopt[2] * currentopt[3] % 2) {currentopt[3]--; currentopt[2]++;}
                            }
                        }
                        clearscreen(scr);
                        click = 1;
                    }
                else if (event.button.button == SDL_BUTTON_LEFT &&
                         row3 && column1)/*kartyaszam balra lepteto*/
                    {
                        if (currentopt[2] != 2 || currentopt[3] != 2)/*azer ilyen hogy a kartyak szama mindig paros legyen*/
                        {
                            if (currentopt[2] < currentopt[3])
                            {
                                currentopt[3]--;
                                if (currentopt[2] * currentopt[3] % 2) {currentopt[3]++; currentopt[2]--;}
                            }
                            else
                            {
                                currentopt[3]++; currentopt[2]--;
                                if (currentopt[2] * currentopt[3] % 2) currentopt[3]--;
                            }
                        }
                        clearscreen(scr);
                        click = 1;
                    }
        }
    }
}

void waitclickscoressmenu(SDL_Surface *scr, char *toquit, CurrentMenu *clickedmenu, int *diff)
{
    int click = 0;
    SDL_Event event;
    while(!click)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                click = *toquit = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && /*ha a vissza gombra kattint -> vissza a fomenube*/
                    event.button.x < scr->w-20 && event.button.x > scr->w-160 &&
                    event.button.y < scr->h-20 && event.button.y > scr->h-70)
                {
                    click = 1;
                    *clickedmenu = MAIN;
                    clearscreen(scr);
                }
                else if(event.button.button == SDL_BUTTON_LEFT && /*ha a nyilakra kattint, akkor ranglistak kozotti valtas*/
                        ((event.button.x < (scr->w/2)-90 && event.button.x > (scr->w/2)-110) ||
                        (event.button.x > (scr->w/2)+90 && event.button.x < (scr->w/2)+110)) &&
                        event.button.y < 445 && event.button.y > 415)
                {
                    click = 1;
                    *diff = *diff ? 0 : 1;
                    clearscreen(scr);
                }
                break;
        }
    }
}

void waitclickwin(SDL_Surface *scr, char *toquit, CurrentMenu *clickedmenu)
{
    int click = 0;
    SDL_Event event;

    while(!click)
    {
        SDL_WaitEvent(&event);
        switch(event.type)/*kattintasra vagy gomb lenyomasra a fomenube jut vissza*/
        {
            case SDL_QUIT:
                *toquit = click = 1;
                break;
            case SDL_KEYDOWN:
                click = 1;
                *clickedmenu = MAIN;
                clearscreen(scr);
                break;
            case SDL_MOUSEBUTTONUP:
                click = 1;
                *clickedmenu = MAIN;
                clearscreen(scr);
                break;
        }
    }
}
