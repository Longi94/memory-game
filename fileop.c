/**
 * @file fileop.c
 * @brief Fajlokkal kapcsolatos fuggvenyek.
 *
 * Fuggvenyei kulombozo fajl muveleteket vegeznek el.
 * Pl.: beolvasas, mentes
 */

#include<stdio.h>
#include<SDL.h>
#include<SDL_ttf.h>
#include"fileop.h"

int fexist(const char *filename)
{
    FILE* fp;
    if ((fp = fopen(filename, "r"))) {fclose(fp); return 1;}
    return 0;
}

void loadconfig(int *optionsarray)
{
    FILE *fp;
    if (!fexist("config.txt"))
    {
        fp = fopen("config.txt", "wt");
        fprintf(fp, "resolution = 0\n");
        fprintf(fp, "difficulty = 0\n");
        fprintf(fp, "cardrow = 2\n");
        fprintf(fp, "cardcolumn = 2\n");
        fprintf(fp, "0\n");
        fclose(fp);
    }
    fp = fopen("config.txt", "rt");
    fscanf(fp, "resolution = %d\n", optionsarray);
    fscanf(fp, "difficulty = %d\n", optionsarray+1);
    fscanf(fp, "cardrow = %d\n", optionsarray+2);
    fscanf(fp, "cardcolumn = %d\n", optionsarray+3);
    fscanf(fp, "%d\n", optionsarray+4);
    fclose(fp);
}

void saveconfig(int *optionsarray)
{
    FILE *fp;
    fp = fopen("config.txt", "wt");
    fprintf(fp, "resolution = %d\n", optionsarray[0]);
    fprintf(fp, "difficulty = %d\n", optionsarray[1]);
    fprintf(fp, "cardrow = %d\n", optionsarray[2]);
    fprintf(fp, "cardcolumn = %d\n", optionsarray[3]);
    fprintf(fp, "%d\n", optionsarray[4]);
    fclose(fp);
}

ScoreList* loadscores(const char *filename)
{
    ScoreList *startelement, *temp, *moving;/*lancolt lista!*/
    int score, time, first = 1, i = 0;
    FILE* fp;

    if (!fexist(filename)) return NULL;
    fp = fopen(filename, "rt");
    while(fscanf(fp, "%d %d\n", &score, &time) != EOF && i < 10)
    {
        temp = (ScoreList*) malloc(sizeof(ScoreList));
        temp->points = score;
        temp->time = time;
        temp->nextelement = NULL;
        if (first)
        {
            startelement = temp;
            moving = temp;
            first = 0;
        }
        else
        {
            moving->nextelement = temp;/*mindig a vegehez fuz*/
            moving = moving->nextelement;
        }
        i++;
    }
    first = fclose(fp);
    return startelement;
}

void savescores(ScoreList *scoreslist, const char *filename)
{
    FILE* fp;

    fp = fopen(filename, "wt");
    for(; scoreslist != NULL; scoreslist = scoreslist->nextelement)/*lancolt lista korbejarasa*/
        fprintf(fp, "%d %d\n", scoreslist->points, scoreslist->time);
    fclose(fp);
}

ScoreList* insertscore(ScoreList *scoreslist, int score, int time)
{
    ScoreList *temp, *moving, *worm;
    temp = (ScoreList*) malloc(sizeof(ScoreList));
    temp->points = score;
    temp->time = time;
    temp->nextelement = NULL;

    /*megkeresi hova kell beszurni:
     *akkor all meg ha a mozgo pointer olyan elemre mutat aminek a kisebb nagyobb,
     *vagy ha olyan elemre mutat aminek a pontszama ugyanazz, de az ideje nagyobb*/
    for (worm = NULL, moving = scoreslist;
    moving != NULL && moving->points >= temp->points && !(moving->points == temp->points && moving->time > temp->time);
    worm = moving, moving = moving->nextelement);

    if (worm == NULL)/*ha az elejen maradt*/
    {
        temp->nextelement = scoreslist;
        return temp;
    }
    else
    {
        worm->nextelement = temp;
        temp->nextelement = moving;
        return scoreslist;
    }
}

void maintainscoreslistsize(ScoreList *scoreslist)
{
    int i;
    ScoreList *temp, *worm = NULL;

    for (i = 0; i < 10; i++, worm = scoreslist, scoreslist = scoreslist->nextelement)/* elmegy a 10 elemig*/
    {
        if (scoreslist == NULL) return;
    }
    for (; scoreslist != NULL; scoreslist = scoreslist->nextelement)/* a tobbit felszabaditja*/
    {
        temp = scoreslist;
        free(scoreslist);
        scoreslist = temp;
    }
    worm->nextelement = NULL;
}

void deletescores(ScoreList *scoreslist, const char *filename)
{
    ScoreList *temp;
    while (scoreslist != NULL)/* felszabaditja az egesz lista*/
    {
        temp = scoreslist->nextelement; /* második elem */
        free(scoreslist);
        scoreslist = temp;
    }
    remove(filename);/*vegul torli a fajlt*/
}
