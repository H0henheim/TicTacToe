#ifndef IA_H
#define IA_H

#include "morpion.h"

void IA_play(char grid[NB][NB], int deepness);
int Max(char grid[NB][NB], int deepness);
int Min(char grid[NB][NB], int deepness);
void nb_series(char grid[NB][NB], int* series_p1, int* series_p2, int n);
int eval(char grid[NB][NB]);
int Winner(char grid[NB][NB]);


#endif
