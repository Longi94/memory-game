#ifndef FILEOP_H_INSERTED
#define FILEOP_H_INSERTED
/*fajl muveeletek*/

/**
 * @typedef ScoreList
 * A ScoreList struktura tipus definicioja.
 */
/**
 * @struct ScoreList
 * @brief Az eredmenyek tarolasara hasznalt lancolt lista strukturaja
 */
typedef struct ScoreList {int points, /**<Egesz tipusus pontszam*/
                          time; /**<Egesz tipusu ido*/
                          struct ScoreList *nextelement; /**<A lista kovetkezo elemere mutato pointer*/
                          } ScoreList;

/**
 * Ellenorzi, hogy letezik-e a megadott nevu fajl.
 * @param filename a fajl neve
 * @return 1 ha letezik, 0 ha nem
 */
int fexist(const char *filename);/*fajl letezes ellenorzese*/

/**
 * A "config.txt" nevu fajlbol betolti a beallitasokat az fexist() segitsegevel. Ha a fajl nem letezik, letrehozza az alap beallitasokkal.
 * @param optionsarray a beallitasokat tartalmazo tomb
 * @see fexist
 */
void loadconfig(int *optionsarray);/*beallitasok betoltese*/

/**
 * A beallitasokat elmenti a "config.txt" nevu fajlba.
 * @param optionsarray a beallitasokat tartalmazo tomb
 */
void saveconfig(int *optionsarray);/*beallitasok mentese*/

/**
 * Betolti fajlbol a ranglistat.
 * @param filename a fajl neve
 * @return a lancolt listara mutato pointer
 */
ScoreList* loadscores(const char *filename);/*eredmenyek betolteset*/

/**
 * Elmenti fajlba a ranglistat.
 * @param scoreslist lancolt lista elso elemere mutato pointer
 * @param filename a fajl neve
 */
void savescores(ScoreList *scoreslist, const char *filename);/*eredmenyek mentese*/

/**
 * Az elert eredmeny beszurja a ranglista lancolt listajaban a megfelelo helyre.
 * @param scoreslist lancolt lista elso elemere mutato pointer
 * @param score az elert pontszam
 * @param time az ido ami alatt a jatek lement
 * @return a lancolt listara mutato pointer
 */
ScoreList* insertscore(ScoreList *scoreslist, int score, int time);

/**
 * A lancolt listat 10 elemure zsugoritja ha annal hosszabb (adatok elvesznek, memoriat szabadit fel).
 * @param scoreslist a lancolt lista elso elemre mutato pointer
 */
void maintainscoreslistsize(ScoreList *scoreslist);

/**
 * Torli a ranglista osszes adatat. Azaz felszabaditja a lancolt listat teljesen es torli a fajlt.
 * @param scoreslist a lancolt lista elso elemre mutato pointer
 * @param filename a fajl neve
 */
void deletescores(ScoreList *scoreslist, const char *filename);

#endif
