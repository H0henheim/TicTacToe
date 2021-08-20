#ifndef MORPION_H
#define MORPION_H

#define NB 3

void showGrid(char[NB][NB]);
void fillGrid(char[NB][NB], int, int, char);
int chekLine(char[NB][NB], int, int);
int outOfBound(int, int);
int fullCell(char[NB][NB], int, int);
void gridInitializer(char[NB][NB]);
int validSpace(char[NB][NB], int, int, int, int);
void Multiplayer();


#endif
