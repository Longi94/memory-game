/**
 * @file draw.c
 * @brief Fuggvenyinek fo feladata a nagyobb elemek kirajzolasa.
 *
 * Fuggvenyei kozt van ami egesz menoket rajzol ki vagy olyan elemeket amyelneknek az eljarasa bonyolult.
 * Ilyen peldaul kartyak kirajzolasa kepfajl betoltesevel.
 */

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include "draw_secondary.h"
#include "gameplayfs.h"
#include "fileop.h"
#include "draw.h"

void drawmainmenu(SDL_Surface *scr)
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Color white = {255,255,255,255}, black = {0,0,0,255};
    font = TTF_OpenFont("arial.ttf",35);
    fonterrorcheck(font);

    /*Fomenu kirajzolasa*/

    text = TTF_RenderUTF8_Blended(font,"Mem\xC3\xB3ria j\xC3\xA1t\xC3\xA9k", white);
    drawtext(scr, text, (scr->w-text->w) / 2, 40);

    /*Jatek gomb*/
    roundedBoxRGBA(scr, scr->w/2-280, 150, scr->w/2-20, 210, 10, 255, 255, 255, 255);
    text = TTF_RenderUTF8_Blended(font, "\xC3\x9Aj j\xC3\xA1t\xC3\xA9k", black);
    drawtext(scr, text, ((scr->w/2-280+scr->w/2-20)-text->w)/2, 150 + (60-text->h)/2);

    /*Betoltes gomb*/
    if (fexist("save.txt")) roundedBoxRGBA(scr, scr->w/2+280, 150, scr->w/2+20, 210, 10, 255, 255, 255, 255);
    else roundedBoxRGBA(scr, scr->w/2+280, 150, scr->w/2+20, 210, 10, 100, 100, 100, 255);
    text = TTF_RenderUTF8_Blended(font, "Bet\xC3\xB6lt\xC3\xA9s", black);
    drawtext(scr, text, ((scr->w/2+280+scr->w/2+20)-text->w)/2, 150 + (60-text->h)/2);

    /*Bealitasok gomb*/
    roundedBoxRGBA(scr, scr->w/2-280, 250, scr->w/2-20, 310, 10, 255, 255, 255, 255);
    text = TTF_RenderUTF8_Blended(font, "Be\xC3\xA1ll\xC3\xADt\xC3\xA1sok", black);
    drawtext(scr, text, ((scr->w/2-280+scr->w/2-20)-text->w)/2, 250 + (60-text->h)/2);

    /*Ranglista gomb*/
    roundedBoxRGBA(scr, scr->w/2+280, 250, scr->w/2+20, 310, 10, 255, 255, 255, 255);
    text = TTF_RenderUTF8_Blended(font, "Ranglista", black);
    drawtext(scr, text, ((scr->w/2+280+scr->w/2+20)-text->w)/2, 250 + (60-text->h)/2);

    /*Kilepes gomb*/
    roundedBoxRGBA(scr, scr->w/2-130, 350, scr->w/2+130, 410, 10, 255, 255, 255, 255);
    text = TTF_RenderUTF8_Blended(font, "Kil\xC3\xA9p\xC3\xA9s", black);
    drawtext(scr, text, (scr->w-text->w)/2, 350 + (60-text->h)/2);

    TTF_CloseFont(font);

    /*Keszitette felirat*/
    font = TTF_OpenFont("arial.ttf",12);
    fonterrorcheck(font);
    text = TTF_RenderUTF8_Blended(font, "K\xC3\xA9sz\xC3\xADtette: Tran Thanh Long", white);
    drawtext(scr, text, 10, scr->h-text->h-10);


    TTF_CloseFont(font);
    font = NULL;
    SDL_Flip(scr);
}

void drawoptionsmenu(SDL_Surface *scr, int *currentopt)
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Color white = {255,255,255,255}, black = {0,0,0,0};
    int i;
    char cardrow[3], cardcolumn[3];
    if (currentopt[3] == 10) sprintf(cardcolumn, "10");
    else if (currentopt[3] == 11) sprintf(cardcolumn, "11");
    else {cardcolumn[0] = currentopt[3]+'0'; cardcolumn[1] = 0;}
    if(currentopt[2] == 10) sprintf(cardrow, "10");
    else {cardrow[0] = currentopt[2]+'0'; cardrow[1] = 0;}

    /*Beallitasok felirat*/
    font = TTF_OpenFont("arial.ttf",35);
    fonterrorcheck(font);
    text = TTF_RenderUTF8_Blended(font,"Be\xC3\xA1ll\xC3\xADt\xC3\xA1sok", white);
    drawtext(scr, text, (scr->w-text->w)/2, 40);

    /*Felbontas opcio*/
    text = TTF_RenderUTF8_Blended(font, "Felbont\xC3\xA1s:", white);
    drawtext(scr, text, (scr->w/2)-text->w-5, 120);

    /*Nehezsegi szint opcio*/
    text = TTF_RenderUTF8_Blended(font, "Neh\xC3\xA9zsegi szint:", white);
    drawtext(scr, text, (scr->w/2)-text->w-5, 170);

    /*Kartyaszam opcio*/
    text = TTF_RenderUTF8_Blended(font, "K\xC3\xA1rtyasz\xC3\xA1m:", white);
    drawtext(scr, text, (scr->w/2)-text->w-5, 220);
    text = TTF_RenderUTF8_Blended(font, "X", white);
    drawtext(scr, text, (scr->w/2)+134, 220);

    /*ranglista torles opcio*/
    text = TTF_RenderUTF8_Blended(font, "Ranglista t\xC3\xB6rl\xC3\xA9se:", white);
    drawtext(scr, text, (scr->w/2)-text->w-5, 270);
    rectangleRGBA(scr, (scr->w/2)+20, 275, (scr->w/2)+50, 305, 255, 255, 255, 255);

    if(currentopt[4]) boxRGBA(scr, (scr->w/2)+25, 280, (scr->w/2)+45, 300, 255, 255, 255, 255);
    SDL_Flip(scr);

    /*Nyilak*/
    for (i = 0; i < 3; i++)
    {
        text = TTF_RenderUTF8_Blended(font, "<", white);
        drawtext(scr, text, scr->w/2+20, 120 + (i*50));
        text = TTF_RenderUTF8_Blended(font, ">", white);
        drawtext(scr, text, scr->w/2+250, 120 + (i*50));
    }

    /*Beallitott opciok*/
    switch(*currentopt) /*felbontas*/
    {
        case 0:
            text = TTF_RenderUTF8_Blended(font, "640x480", white);
            break;
        case 1:
            text = TTF_RenderUTF8_Blended(font, "800x600", white);
            break;
        case 2:
            text = TTF_RenderUTF8_Blended(font, "1024x768", white);
            break;
    }
    drawtext(scr, text, (scr->w+270-text->w)/2+10, 120);

    switch(currentopt[1]) /*nehezseg*/
    {
        case (0):
            text = TTF_RenderUTF8_Blended(font, "k\xC3\xB6nny\xC5\xB1", white);
            break;
        case (1):
            text = TTF_RenderUTF8_Blended(font, "neh\xC3\xA9z", white);
            break;
    }
    drawtext(scr, text, (scr->w+270-text->w)/2+10, 170);

    /*kartya szam*/
    text = TTF_RenderUTF8_Blended(font, cardrow, white);
    drawtext(scr, text, scr->w/2+90, 220);
    text = TTF_RenderUTF8_Blended(font, cardcolumn, white);
    drawtext(scr, text, scr->w/2+180, 220);

    TTF_CloseFont(font);

    /*Alkalmaz gomb*/
    font = TTF_OpenFont("arial.ttf", 24);
    fonterrorcheck(font);
    roundedBoxRGBA(scr, scr->w-20, scr->h-70, scr->w-160, scr->h-20, 5, 255, 255, 255, 255);
    text = TTF_RenderUTF8_Blended(font, "Alkalmaz", black);
    drawtext(scr, text, scr->w-90-(text->w/2), scr->h-45-(text->h/2));

    TTF_CloseFont(font);

    /*Keszitette felirat*/
    font = TTF_OpenFont("arial.ttf",12);
    fonterrorcheck(font);
    text = TTF_RenderUTF8_Blended(font, "K\xC3\xA9sz\xC3\xADtette: Tran Thanh Long", white);
    drawtext(scr, text, 10, scr->h-text->h-10);

    TTF_CloseFont(font);
    font = NULL;
    SDL_Flip(scr);
}

void drawscoresmenu(SDL_Surface *scr, ScoreList *scoreslist, int *diff)
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Color white = {255,255,255,255}, black = {0,0,0,0};
    int i, tabley;
    char string[6];

    /*Ranglista felirat*/
    font = TTF_OpenFont("arial.ttf",35);
    fonterrorcheck(font);
    text = TTF_RenderUTF8_Blended(font,"Ranglista", white);
    drawtext(scr, text, (scr->w-text->w)/2, 40);

    if(*diff) text = TTF_RenderUTF8_Blended(font,"Neh\xC3\xA9z", white);
    else text = TTF_RenderUTF8_Blended(font,"K\xC3\xB6nny\xC5\xB1", white);
    drawtext(scr, text, (scr->w-text->w)/2, 410);

    text = TTF_RenderUTF8_Blended(font, "<", white);
    drawtext(scr, text, scr->w/2-100 - (text->w / 2), 410);
    text = TTF_RenderUTF8_Blended(font, ">", white);
    drawtext(scr, text, scr->w/2+100 - (text->w / 2), 410);

    /*Tablazat*/
    for (i = 0, tabley = 127; i < 11; i++, tabley +=27) rectangleRGBA(scr, scr->w/2-250, 100, scr->w/2+250, tabley, 255, 255, 255, 255);
    vlineRGBA(scr, scr->w/2, 100, tabley - 27, 255, 255, 255, 255);

    TTF_CloseFont(font);

    /*Tablazat tartalma*/
    font = TTF_OpenFont("arial.ttf",20);
    text = TTF_RenderUTF8_Blended(font, "Pontsz\xC3\xA1m", white);
    drawtext(scr, text, scr->w / 2 - 245, 102);
    text = TTF_RenderUTF8_Blended(font, "Id\xC5\x91", white);
    drawtext(scr, text, scr->w / 2 + 5, 102);
    if (scoreslist != NULL)
    {
    for (tabley = 129; scoreslist != NULL; scoreslist = scoreslist->nextelement, tabley += 27)
        {
            sprintf(string, "%d", scoreslist->points);
            text = TTF_RenderUTF8_Blended(font, string, white);
            drawtext(scr, text, scr->w / 2 - 245, tabley);

            sprintf(string, "%d%d:%d%d", scoreslist->time / 60 / 10, (scoreslist->time / 60) % 10, scoreslist->time % 60 / 10, scoreslist->time % 60 % 10);
            text = TTF_RenderUTF8_Blended(font, string, white);
            drawtext(scr, text, scr->w / 2 + 5, tabley);
        }
    }

    TTF_CloseFont(font);

    /*Vissza gomb*/
    font = TTF_OpenFont("arial.ttf", 24);
    fonterrorcheck(font);
    roundedBoxRGBA(scr, scr->w-20, scr->h-70, scr->w-160, scr->h-20, 5, 255, 255, 255, 255);
    text = TTF_RenderUTF8_Blended(font, "Vissza", black);
    drawtext(scr, text, scr->w-90-(text->w/2), scr->h-45-(text->h/2));

    /*Keszitette felirat*/
    TTF_CloseFont(font);
    font = TTF_OpenFont("arial.ttf",12);
    fonterrorcheck(font);
    text = TTF_RenderUTF8_Blended(font, "K\xC3\xA9sz\xC3\xADtette: Tran Thanh Long", white);
    drawtext(scr, text, 10, scr->h-text->h-10);

    TTF_CloseFont(font);
    font = NULL;
    SDL_Flip(scr);
}

void drawnewgame(SDL_Surface *scr)
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Color white = {255,255,255,255};

    hlineRGBA(scr, 0, scr->w, 40, 255, 255, 255, 255); /* also es felso vonalak*/
    hlineRGBA(scr, 0, scr->w, scr->h-40, 255, 255, 255, 255);

    font = TTF_OpenFont("arial.ttf",30);
    fonterrorcheck(font);

    /*mentes es kilepes*/
    text = TTF_RenderUTF8_Blended(font, "Ment\xC3\xA9s \xC3\xA9s kil\xC3\xA9p\xC3\xA9s", white);
    drawtext(scr, text, scr->w-5-text->w, scr->h-5-text->h);

    /*ido*/
    text = TTF_RenderUTF8_Blended(font, "Id\xC5\x91: 00:00", white);
    drawtext(scr, text, scr->w-5-text->w, 5);

    /*pontszam*/
    text = TTF_RenderUTF8_Blended(font, "Pontsz\xC3\xA1m:", white);
    drawtext(scr, text, 5, 5);

    text = TTF_RenderUTF8_Blended(font, "0", white);
    drawtext(scr, text, 160, 5);

    /*mgetalalt parok*/
    text = TTF_RenderUTF8_Blended(font, "Megtal\xC3\xA1lt p\xC3\xA1rok:", white);
    drawtext(scr, text, 5, scr->h-5-text->h);

    text = TTF_RenderUTF8_Blended(font, "0", white);
    drawtext(scr, text, 220, scr->h-5-text->h);

    TTF_CloseFont(font);
    font = NULL;
    SDL_Flip(scr);
}

void drawcards(SDL_Surface *scr, int rows, int columns, int cardsize, int diff)
{
    SDL_Surface *image;
    int xcoord, ycoord, irows, jcolumns;
    SDL_Rect imagecoord = {0,0,0,0};
    if (diff) image = rotozoomSurface(IMG_Load("hardim/cardback.jpg"),0, cardsize / 256.0, 1);/*megfelelo meretuve le zsugoritja a kartyat*/
    else image = rotozoomSurface(IMG_Load("images/cardback.jpg"),0, cardsize / 256.0, 1);
    for (ycoord = (scr->h - (rows*cardsize + (rows-1)*5))/2, irows = 0; irows < rows; ycoord += cardsize + 5, irows++)
        for (xcoord = (scr->w - (columns*cardsize + (columns-1)*5))/2, jcolumns = 0; jcolumns < columns; xcoord += cardsize + 5, jcolumns++)
        {
            imagecoord.x = xcoord;
            imagecoord.y = ycoord;
            SDL_BlitSurface(image, NULL, scr, &imagecoord);
        }
    SDL_FreeSurface(image);
    image = NULL;
    SDL_Flip(scr);
}

void drawonecard(SDL_Surface *scr, int xcoord, int ycoord, int cardsize, const char *filename)
{
    SDL_Surface *image;
    SDL_Rect imagecoord = {0,0,0,0};
    image = rotozoomSurface(IMG_Load(filename), 0, cardsize / 256.0, 1);
    imagecoord.x = xcoord;
    imagecoord.y = ycoord;
    SDL_BlitSurface(image, NULL, scr, &imagecoord);
    SDL_FreeSurface(image);
    image = NULL;
}

void redrawfoundpairs (SDL_Surface *scr, int foundpairs)
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Color white = {255,255,255,255};
    char number[3];

    boxRGBA(scr, 220, scr->h-39, 300, scr->h, 0, 0, 0, 255);
    font = TTF_OpenFont("arial.ttf",30);
    fonterrorcheck(font);
    sprintf(number, "%d", foundpairs);
    text = TTF_RenderUTF8_Blended(font, number, white);
    drawtext(scr, text, 220, scr->h-5-text->h);
    TTF_CloseFont(font);
    font = NULL;
    SDL_Flip(scr);
}

void redrawtime (SDL_Surface *scr, int time)
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Color white = {255,255,255,255};
    char normaltimeformat[6];

    font = TTF_OpenFont("arial.ttf",30);
    fonterrorcheck(font);
    sprintf(normaltimeformat, "%d%d:%d%d", time / 60 / 10, (time / 60) % 10, time % 60 / 10, time % 60 % 10);/*az ido megformazasa*/
    text = TTF_RenderUTF8_Blended(font, normaltimeformat, white);
    boxRGBA(scr, scr->w-90, 5, scr->w, 39, 0, 0, 0, 255);
    drawtext(scr, text, scr->w-5-text->w, 5);
    TTF_CloseFont(font);
    font = NULL;
    SDL_Flip(scr);
}

void redrawscore (SDL_Surface *scr, int score)
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Color white = {255,255,255,255};
    char number[5];

    boxRGBA(scr, 160, 0, 300, 39, 0, 0, 0, 255);
    font = TTF_OpenFont("arial.ttf",30);
    fonterrorcheck(font);
    sprintf(number, "%d", score);
    text = TTF_RenderUTF8_Blended(font, number, white);
    drawtext(scr, text, 160, 5);
    TTF_CloseFont(font);
    font = NULL;
    SDL_Flip(scr);
}

void drawwin(SDL_Surface *scr, int score, int time)
{
    TTF_Font *font;
    SDL_Surface *text;
    SDL_Color white = {255,255,255,255};
    char pontszam[30];
    char ido[30];

    sprintf(pontszam, "Pontszamod: %d", score);
    sprintf(ido, "Idod: %d%d:%d%d", time / 60 / 10, (time / 60) % 10, time % 60 / 10, time % 60 % 10);

    font = TTF_OpenFont("arial.ttf", 30);

    text = TTF_RenderUTF8_Blended(font, "Nyert\xC3\xA9l", white);
    drawtext(scr, text, (scr->w - text->w) / 2, 100);
    text = TTF_RenderUTF8_Blended(font, pontszam, white);
    drawtext(scr, text, (scr->w - text->w) / 2, 200);
    text = TTF_RenderUTF8_Blended(font, ido, white);
    drawtext(scr, text, (scr->w - text->w) / 2, 300);
}
