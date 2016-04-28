/**
 * @file gameplayfs.c
 * @brief A startnewgame() altal hasznalt fuggvenyek.
 *
 * Ez tartalmazza a jatek vezerlesehez szukseges fuggvenyeket.
 * @see gameplay.c
 */
#include<SDL.h>
#include<stdlib.h>
#include<time.h>
#include"draw.h"
#include"gameplayfs.h"
#include"fileop.h"

CardProp **alloc_dyn_2darray(int rows, int columns)
{
    int i;
    CardProp **ptrarray;
    ptrarray = (CardProp**) malloc(rows*sizeof(CardProp*));
    if (ptrarray == NULL)
    {
        fprintf(stderr, "Failed to allocate memory."); /*hibaellenorzes*/
        exit(1);
    }
    ptrarray[0] = (CardProp*) malloc(columns*rows*sizeof(CardProp));
    if (ptrarray[0] == NULL)
    {
        fprintf(stderr, "Failed to allocate memory."); /*hibaellenorzes*/
        exit(1);
    }
    for (i = 1; i < rows; i++)
        ptrarray[i] = ptrarray[0] + i*columns;
    return ptrarray;
}

void free_dyn_2darray(CardProp **ptrarray)
{
    free(ptrarray[0]);
    free(ptrarray);
}

void generate_random_pairs(CardProp *cardarray, int rows, int columns)
{
    CardProp *backup;
    int end=0, pair=0, current = 1, placed = 0, number, i;
    backup = cardarray;/*pointer lemasolasa (mert megvaltozik)*/
    srand(time(0));/*gep ideje szerinti randomizacio*/
    for (i=0; i < rows*columns; cardarray++, i++) cardarray->cindex = 0;/*ki nullaz*/
    while(!end)
    {
        i = 0;
        cardarray = backup;/*pointer visszaallaitasa*/
        number = rand() % (rows*columns-placed);/*random hely generalasa a megmaradt helyekbol (linearis)*/
        while(number-i)/*a hley megkeresese*/
        {
            if (cardarray->cindex == 0) i++;
            cardarray++;
        }
        while (cardarray->cindex)cardarray++;/*ha nem nulla helyre lep, addig megy tovabb, amig nulla nem lesz*/
        cardarray->cindex = current;/*beiras*/
        placed++;/*eggyel tobb kartya lett elhelyezve*/
        current = pair == 0 ? current : current + 1;/*ha meg van a par, masik szam*/
        pair = pair ? 0 : 1;/*par?*/
        end = placed == rows*columns;/*akkor all meg ha betoltodott*/
    }
    cardarray = backup;/*pointer vissza allitasa*/
}

int deter_cardsize(int rows, int columns, int windowh, int windoww)
{
    int a, b;
    a = (windoww-(2*10)-(5*(columns-1)))/columns;
    b = ((windowh-80)-(2*10)-(5*(rows-1)))/rows;
    if (a>b) return b; /*a kissebbet adja vissza hogy elferjenek a kartyak*/
    return a;
}

int deter_clickedcard_row(int rows, int windowh, int cardsize, int clickedy)
{
    int i, space, found;
    found = i = 0;
    space = (windowh - 80 - rows*cardsize - ((rows-1)*5)) / 2;/* a kartyak folotti ores hely*/
    while (i < rows)
    {
        if (((space+40 + (cardsize + 5)*i) < clickedy) && (((space+40 + (cardsize + 5)*i) + cardsize) > clickedy)) return i;/*xkoordinata alapjan*/
        i++;
    }
    return -1;
}

int deter_clickedcard_column(int columns, int windoww, int cardsize, int clickedx)
{
    int i, space, found;
    found = i = 0;
    space = (windoww - columns*cardsize - ((columns-1)*5)) / 2;/*a kartyaktol jobbra levo ures hely*/
    while (i < columns)
    {
        if ((space + (cardsize + 5)*i < clickedx) && (space + (cardsize + 5)*i + cardsize > clickedx)) return i;/*ykoordinata utan*/
        i++;
    }
    return -1;
}

Uint32 gametimer(Uint32 ms, void *param)
{
    SDL_Event event;
    event.type = SDL_USEREVENT;/*generalas*/
    SDL_PushEvent(&event);
    return ms;
}

void savegame(int rows, int columns, int difficulty, int score, int time, int pairsfound, CardProp **cards)
{
    int i, j;
    FILE *fp;
    fp = fopen("save.txt", "wt");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open save.txt");
        exit(1);
    }
    fprintf(fp, "%d %d %d %d %d %d\n", rows, columns, difficulty, score, time, pairsfound);/*formazott fajlba iras*/
    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            fprintf(fp, "%d %d\n", cards[i][j].cindex, cards[i][j].flipped);/*egysorban  kartyak adatai, minden sorban mas kartya*/
    fclose(fp);
}

void loadgamedata(int *rows, int *columns, int *difficulty, int *score, int *time, int *pairsfound)
{
    FILE *fp;
    fp = fopen("save.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open save.txt");
        exit(1);
    }
    fscanf(fp, "%d %d %d %d %d %d\n", rows, columns, difficulty, score, time, pairsfound);/*csak az elso sort olvassa be*/
    fclose(fp);
}

void loadgamestate(int rows, int columns, CardProp **cards)
{
    int i, j, temp1, temp2, temp3, temp4, temp5, temp6;
    FILE *fp;
    fp = fopen("save.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open save.txt");
        exit(1);
    }
    fscanf(fp, "%d %d %d %d %d %d\n",&temp1,&temp2,&temp3,&temp4,&temp5,&temp6);/*mivel meg nem ismertem az fseek()-et*/
    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            fscanf(fp, "%d %d\n", &cards[i][j].cindex, &cards[i][j].flipped);/*kartyak adatainek formazott beolvasasa*/
    fclose(fp);
}

void drawfoundpairs(SDL_Surface *scr, int rows, int columns, CardProp **cards, int spacec, int spacer, int cardsize, int diff)
{
    int i, j;
    char imagename[15];
    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            if (cards[i][j].flipped)
            {
                if (diff) sprintf(imagename, "hardim/%d.jpg", cards[i][j].cindex);/*nehezseg alapjan donti el, hogy melyik kepet kell beolvasni*/
                else sprintf(imagename, "images/%d.jpg", cards[i][j].cindex);
                drawonecard(scr, spacec + j*(cardsize+5), spacer + 40 + i*(cardsize+5), cardsize, imagename);
            }
}
