/**
 * @file main.c
 * @brief A fo program.
 *
 * Ez vezerli le az egesz programot a tobbi forrasfajlban levo fuggvenyek segitsegevel.\n
 * A program megnyitasakor eloszor beolti a beallitasokat es a ranglistat. A ranglistat ket kulombozo fajlban tarolja el, hogy a
 * nehezseget megkulomboztesse. Inicializalja az SDL-t es a TTF-t. A beallitsokban megadott meratu ablakot nyit meg. Egy switchben
 * kezeli menuket. A benne levo "menu" valtozot kulombozo fuggvenyek valtoztajak meg menu valtaskor.
 * A program az ablakot bezarja, ha a felhasznalalo a kilepesre kattint vagy az ablak piros X gombjara.
 * Elmenti a beallitasokat, a ranglistat (ha van), kilep az SDL-bol es vegul bezarul a program.
 * @see CurrentMenu
 */

#include <stdio.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "draw.h"
#include "waitclick.h"
#include "gameplay.h"
#include "fileop.h"

int main(int argc, char *argv[]) {
    SDL_Surface *screen;
    CurrentMenu menu;
    ScoreList *easyscoreslist, *hardscoreslist;
    char quit = 0;
    int windowwidth, windowheight, loadsavedgame, removed = 0, gamescore, gametime, gamediff;
    int options[6];/*0 = felbontas, 1 = nehezseg, 2 = sor, 3 = oszlop, 4 = eredmenyek torles, 5 = changedres*/

    menu = MAIN;

    loadconfig(options);
    options[5] = options[0]+1;

    easyscoreslist = loadscores("scores1.txt");
    hardscoreslist = loadscores("scores2.txt");

    TTF_Init();

    while(!quit)
    {
        if (options[5] != options[0])/*ha megvaltoztatta a felbontast (bezart az ablakot) nyissa meg ujra az abalakot (uj ablak meret)*/
        {
            options[5] = options[0];
            switch (options[0])
            {
                case 0:
                    windowwidth = 640;
                    windowheight = 480;
                    break;
                case 1:
                    windowwidth = 800;
                    windowheight = 600;
                    break;
                case 2:
                    windowwidth = 1027;
                    windowheight = 768;
                    break;
            }
            /*SDL inicializalasa es ablak megnyitasa*/
            SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
            screen=SDL_SetVideoMode(windowwidth, windowheight, 0, SDL_ANYFORMAT);
            if (!screen) {
                fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
                exit(1);
            }
            SDL_WM_SetCaption("Mem\xC3\xB3ria j\xC3\xA1t\xC3\xA9k", "Mem\xC3\xB3ria j\xC3\xA1t\xC3\xA9k");
        }
        switch(menu)
        {
            case MAIN:
                gamediff = 0;
                if (options[4])/*ranglista torles pipa*/
                {
                    deletescores(easyscoreslist, "scores1.txt");
                    deletescores(hardscoreslist, "scores2.txt");
                    easyscoreslist = hardscoreslist = NULL;
                    options[4] = 0;
                }
                drawmainmenu(screen);
                waitclickmainmenu(screen, &quit, &menu);
                break;
            case OPTIONS:
                drawoptionsmenu(screen, options);
                waitclickoptionsmenu(screen, &quit, &menu, options);
                if (options[5] != options[0]) SDL_Quit(); /*ha megvaltoztatta a felbontast, zarja be az ablakot,
                                                            majd megnyitja ujra az uj merettel*/
                break;
            case NEWGAME:
                loadsavedgame = 0;
                startnewgame(screen, options, &menu, &quit, loadsavedgame, &gamescore, &gametime, &gamediff);
                break;
            case LOADGAME:
                loadsavedgame = 1;
                startnewgame(screen, options, &menu, &quit, loadsavedgame, &gamescore, &gametime, &gamediff);
                break;
            case SCORES:
                if (gamediff) drawscoresmenu(screen, hardscoreslist, &gamediff);
                else drawscoresmenu(screen, easyscoreslist, &gamediff);
                waitclickscoressmenu(screen, &quit, &menu, &gamediff);
                break;
            case WIN:
                removed = remove("save.txt");/*troli a mentes fajlt, ezalatl nem tudnak a betoltes gombra kattintani*/
                if (gamediff) hardscoreslist = insertscore(hardscoreslist, gamescore, gametime);
                else easyscoreslist = insertscore(easyscoreslist, gamescore, gametime);
                maintainscoreslistsize(easyscoreslist);
                maintainscoreslistsize(hardscoreslist);
                waitclickwin(screen, &quit, &menu);
                break;
        }
    }

    saveconfig(options);
    if (easyscoreslist != NULL) savescores(easyscoreslist, "scores1.txt");
    if (hardscoreslist != NULL) savescores(hardscoreslist, "scores2.txt");

    SDL_Quit();
    return 0;
}
