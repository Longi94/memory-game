/**
 * @file gameplay.c
 * @brief A jatekot vezerlo fuggveny.
 *
 * Egy fuggvenyt tartalmaz, ami magat a jatekot vezerli.
 */

#include<SDL.h>
#include<SDL_gfxPrimitives.h>
#include<SDL_ttf.h>
#include"waitclick.h"
#include"draw.h"
#include"draw_secondary.h"
#include"fileop.h"
#include"gameplayfs.h"
#include"gameplay.h"

void startnewgame(SDL_Surface *scr, int *options, CurrentMenu *clickedmenu, char *toquit, int loadsavedgame, int *gamescore, int *gametime, int *gamediff)
{
    CardProp **cards;
    PlayState pstate;
    int cardsize, playing = 1, xcard, ycard, spacec, spacer, i, j, xflipped, yflipped, rows, columns, score, time, pairsfound;
    SDL_Event event;
    char imagename[15];
    SDL_TimerID timer;

    pstate = WAIT;

    if (loadsavedgame)/*ha a jatek betoltesere kattintott*/
    {
        loadgamedata(&rows, &columns, gamediff, &score, &time, &pairsfound);
        cards = alloc_dyn_2darray(rows, columns);
        loadgamestate(rows, columns, cards);
    }
    else/*kulonben uj jatek*/
    {
        *gamediff = options[1];
        rows = options[2];
        columns = options[3];
        cards = alloc_dyn_2darray(rows, columns);
        generate_random_pairs(cards[0], columns, rows);
        for (i = 0; i < rows; i++)
            for (j = 0; j < columns; j++)
                cards[i][j].flipped = 0;/*kinullaz*/
        pairsfound = score = time = 0;
    }

    cardsize = deter_cardsize(rows, columns, scr->h, scr->w);
    spacec = (scr->w - columns*cardsize - ((columns-1)*5))/2; /*kartyaltol jobbra levo ures hely*/
    spacer = (scr->h - 80 - rows*cardsize - ((rows-1)*5))/2;/*kartyak feletti ures hely*/

    /*mident megrajzol amit kell*/
    drawnewgame(scr);
    drawcards(scr, rows, columns, cardsize, *gamediff);
    drawfoundpairs(scr, rows, columns, cards, spacec, spacer, cardsize, *gamediff);
    redrawfoundpairs(scr, pairsfound);
    redrawscore(scr, score);
    redrawtime(scr, time);
    SDL_Flip(scr);

    timer = SDL_AddTimer(1000, gametimer, NULL);/*idozito az idomeronek*/

    while(playing)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:/*piros x -> kilep*/
                savegame(rows, columns, *gamediff, score, time, pairsfound, cards);
                SDL_RemoveTimer(timer);
                playing = 0;
                *clickedmenu = MAIN;
                if (pstate == SELECTED)/*ha egy kartya ki volt valasztva akkor az ne maradjon felforditva betolteskor*/
                {
                    cards[yflipped][xflipped].flipped = 0;
                }
                *toquit = 1;
                break;
            case SDL_MOUSEBUTTONUP: /*kattintas*/
                if (event.button.button == SDL_BUTTON_LEFT && event.button.x > scr->w - 242 && event.button.y > scr->h - 40) /*ha a mentes es kilepésra kettint ---> egyenlore csak a fomenube lep*/
                {
                    playing = 0;
                    *clickedmenu = MAIN;
                    if (pstate == SELECTED)/*ha egy kartya ki volt valasztva akkor az ne maradjon felforditva betolteskor*/
                    {
                        cards[yflipped][xflipped].flipped = 0;
                    }
                    savegame(rows, columns, *gamediff, score, time, pairsfound, cards);
                    SDL_RemoveTimer(timer);
                    clearscreen(scr);
                }
                else if (event.button.button == SDL_BUTTON_LEFT)
                {
                    xcard = deter_clickedcard_column(columns, scr->w, cardsize, event.button.x);
                    ycard = deter_clickedcard_row(rows, scr->h, cardsize, event.button.y);
                    if (xcard != -1 && ycard != -1)/*ha kartyara kattintott (xcard. oszlop, ycard. sor)*/
                    {
                        switch (pstate)
                        {
                            case WAIT:/*elso kartya*/
                                if (!cards[ycard][xcard].flipped)/*csak akkor ha eredetileg le vorlt forditva*/
                                {
                                    cards[ycard][xcard].flipped = 1;
                                    if (*gamediff) sprintf(imagename, "hardim/%d.jpg", cards[ycard][xcard].cindex); /* a kartyahoz tartozo kepet keresi meg*/
                                    else sprintf(imagename, "images/%d.jpg", cards[ycard][xcard].cindex);
                                    drawonecard(scr, spacec + xcard*(cardsize+5), spacer + 40 + ycard*(cardsize+5), cardsize, imagename);/*kirazolja a kartyahoz tartozo kepet*/
                                    SDL_Flip(scr);
                                    xflipped = xcard;
                                    yflipped = ycard;
                                    pstate = SELECTED;
                                }
                                break;
                            case SELECTED:/*masodik kartya*/
                                if (!cards[ycard][xcard].flipped)/*csak akkor ha eredetilg le volt forditva*/
                                {
                                    cards[ycard][xcard].flipped = 1;
                                    if (*gamediff) sprintf(imagename, "hardim/%d.jpg", cards[ycard][xcard].cindex);
                                    else sprintf(imagename, "images/%d.jpg", cards[ycard][xcard].cindex); /* a kartyahoz tartozo kepet keresi meg*/
                                    drawonecard(scr, spacec + xcard*(cardsize+5), spacer + 40 + ycard*(cardsize+5), cardsize, imagename);/*kirazolja a kartyahoz tartozo kepet*/
                                    SDL_Flip(scr);
                                    if (cards[ycard][xcard].cindex != cards[yflipped][xflipped].cindex)
                                    {
                                        SDL_Delay(500);/*fel masodpercig maradjanak felforditva*/
                                        if (*gamediff)/*a kartyak visszaforditasa*/
                                        {
                                            drawonecard(scr, spacec + xcard*(cardsize+5), spacer + 40 + ycard*(cardsize+5), cardsize, "hardim/cardback.jpg");
                                            drawonecard(scr, spacec + xflipped*(cardsize+5), spacer + 40 + yflipped*(cardsize+5), cardsize, "hardim/cardback.jpg");
                                        }
                                        else
                                        {
                                            drawonecard(scr, spacec + xcard*(cardsize+5), spacer + 40 + ycard*(cardsize+5), cardsize, "images/cardback.jpg");
                                            drawonecard(scr, spacec + xflipped*(cardsize+5), spacer + 40 + yflipped*(cardsize+5), cardsize, "images/cardback.jpg");
                                        }

                                        cards[ycard][xcard].flipped = 0;
                                        cards[yflipped][xflipped].flipped = 0;
                                        score -= 1;/*pont levonas ha nem talalt part*/
                                        redrawscore(scr, score);
                                    }
                                    else
                                    {
                                        pairsfound++;/*part talalt*/
                                        score += 10;
                                        redrawfoundpairs(scr, pairsfound);
                                        redrawscore(scr, score);
                                        if (pairsfound == rows*columns/2)/*ha megtalalta az osszes part*/
                                        {
                                            playing = 0;/*vege*/
                                            *gamescore = score;
                                            *gametime = time;
                                            clearscreen(scr);
                                            drawwin(scr, score, time);
                                            *clickedmenu = WIN;
                                        }
                                    }
                                    SDL_Flip(scr);
                                    pstate = WAIT;
                                }
                                break;
                        }
                    }
                }
                break;
            case SDL_USEREVENT:
                if (time < 6039) time++;/*ido folyamatos novelese 99:99-ig, ott megall*/
                redrawtime(scr, time);
                break;
        }
    }
    SDL_RemoveTimer(timer);
    free_dyn_2darray(cards);
}
