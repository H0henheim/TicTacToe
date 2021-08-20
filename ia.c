#include <stdio.h>
#include <stdlib.h>
#include "ia.h"

#define INI ' '
char cross = 'X';
char circle = 'O';


int Winner(char grid[NB][NB])
{
	int i,j;
	int p1,p2;

	nb_series(grid,&p1,&p2,3);

	if(p1){
		return 1;
	}
	else if(p2){
		return 2;
	}
	else
	{
		//Si jeu non fini et personne n'a gagne, retourne 0
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(grid[i][j] == INI)
					return 0;
			}
		}
	}

	//jeu fini personne n'a gagne, retourne 3
	return 3;
}

void nb_series(char grid[NB][NB], int* series_p1, int* series_p2, int n)
{
	int cpt1, cpt2, i, j;

	*series_p1 = 0;
	*series_p2 = 0;

	cpt1 = 0;
	cpt2 = 0;

	//Diagonale descendante
	for(i=0;i<3;i++)
	{
		if(grid[i][i] == cross)
		{
			cpt1++;
			cpt2 = 0;

			if(cpt1 == n){
				(*series_p1)++;
			}
		}
		else if(grid[i][i] == circle)
		{
			cpt2++;
			cpt1 = 0;

			if(cpt2 == n){
				(*series_p2)++;
			}
		}
	}


	cpt1 = 0;
	cpt2 = 0;

	//Diagonale montante
	for(i=0;i<3;i++)
	{
		if(grid[i][2-i] == cross)
		{
			cpt1++;
			cpt2 = 0;

			if(cpt1 == n){
				(*series_p1)++;
			}

		}
		else if(grid[i][2-i] == circle)
		{
			cpt2++;
			cpt1 = 0;

			if(cpt2 == n){
				(*series_p2)++;
			}
		}
	}

	//En ligne
	for(i=0;i<3;i++)
	{
		cpt1=0;
		cpt2=0;

		//Horizontalement
		for(j=0;j<3;j++)
		{
			if(grid[i][j] == cross)
			{
				cpt1++;
				cpt2 = 0;

				if(cpt1 == n){
					(*series_p1)++;
				}
			}
			else if(grid[i][j] == circle)
			{
				cpt2++;
				cpt1 = 0;

				if(cpt2 == n){
					(*series_p2)++;
				}
			}
		}

		cpt1 = 0;
		cpt2 = 0;

		//Verticalement
		for(j=0;j<3;j++)
		{
			if(grid[j][i] == cross)
			{
				cpt1++;
				cpt2 = 0;

				if(cpt1 == n){
					(*series_p1)++;
				}
			}
			else if(grid[j][i] == circle)
			{
				cpt2++;
				cpt1 = 0;

				if(cpt2 == n){
					(*series_p2)++;
				}
			}
		}
	}
}

int eval(char grid[NB][NB])
{
	int winner,nb_paws = 0;
	int i,j;

	//On compte le nombre de pions présents sur le plateau
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(grid[i][j] != INI)
				nb_paws++;
		}
	}

	if( (winner = Winner(grid)) != 0 )
	{
		if(winner == 1)
			return (1000 - nb_paws);
		else if(winner == 2)
			return (-1000 + nb_paws);
		else
			return 0;
	}

	//On compte le nombre de series de 2 pions alignes de chacun des joueurs
	int series_p1 = 0;
	int series_p2 = 0;
	nb_series(grid,&series_p1,&series_p2,2);

	return series_p1 - series_p2;
}

int Min(char grid[NB][NB], int deepness)
{
	if(deepness == 0 || Winner(grid) != 0)
		return eval(grid);

	int min = 10000;
	int i,j,tmp;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(grid[i][j] == INI)
			{
				grid[i][j] = cross; /*circle;*/
				tmp = Max(grid, deepness-1);

				if(tmp < min || ( (tmp == min) && (rand()%2 == 0) ) ) //A checker --> rand ne fait pas jouer le meilleur coup ?
					min = tmp;

				grid[i][j] = INI;
			}
		}
	}
    printf("\nvaleur min : %d\n", min);
	return min;
}

int Max(char grid[NB][NB], int deepness)
{
	if(deepness == 0 || Winner(grid) != 0)
		return eval(grid);

	int max = -10000;
	int i,j,tmp;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(grid[i][j] == INI)
			{
				grid[i][j] = circle;/*cross;*/
				tmp = Min(grid, deepness-1);

				if(tmp > max || ( (tmp == max) && (rand()%2 ==0) ) ) //A checker --> rand ne fait pas jouer le meilleur coup ?
					max = tmp;

				grid[i][j] = INI;
			}
		}
	}

	return max;
}


void IA_play(char grid[NB][NB], int deepness)
{
	int max = -10000;
	int tmp = 0; int maxi = 0; int maxj = 0;
	int i,j;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(grid[i][j] == INI)
			{
				grid[i][j] = cross; /*circle;*/
				tmp = Min(grid,deepness-1);

				if(tmp > max || ( (tmp == max) && (rand()%2 ==0) ) ) //A checker --> rand ne fait pas jouer le meilleur coup ?
				{
					max = tmp;
					maxi = i;
					maxj = j;
				}
				grid[i][j] = INI;
			}
		}
	}

	grid[maxi][maxj] = circle;
    showGrid(grid);
}

