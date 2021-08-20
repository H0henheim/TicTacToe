#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ia.h"

#define INI ' '
#define PROFONDEUR 5

char CROSS = 'X';
char CIRCLE = 'O';

void showGrid(char grid[NB][NB])
{
	system("clear");
	printf("+---+---+---+\n");
	printf("| %c | %c | %c |\n", grid[0][0], grid[1][0], grid[2][0]);
	printf("+---+---+---+\n");
	printf("| %c | %c | %c |\n", grid[0][1], grid[1][1], grid[2][1]);
	printf("+---+---+---+\n");
	printf("| %c | %c | %c |\n", grid[0][2], grid[1][2], grid[2][2]);
	printf("+---+---+---+\n");

	printf("\n");
}


void fillGrid(char grid[NB][NB], int x, int y, char c)
{
	grid[x-1][y-1] = c;
}


int chekLine(char grid[NB][NB], int x, int y)
{
	x--; y--;
	if(grid[x][0] == grid[x][1] && grid[x][0] == grid[x][2] && grid[x][0] != ' ')
		return 1;
	else if(grid[0][y] == grid[1][y] && grid[0][y] == grid[2][y] && grid[0][y] != ' ')
		return 1;
	else if(grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2] && grid[0][0] != ' ')
		return 1;
	else if(grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0] && grid[0][2] != ' ')
		return 1;
	else
		return 0;
}

int outOfBound(int x, int y)
{
	if(x < 1 || x > 5)
		return 0;
	else if(y < 1 || y > 5)
		return 0;
	return 1;
}

int fullCell(char grid[NB][NB], int x, int y)
{
	if(grid[x-1][y-1] == INI)
		return 1;
	return 0;
}

void gridInitializer(char grid[NB][NB])
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			grid[i][j] = INI;
}

int validSpace(char grid[NB][NB], int oldX, int oldY, int x, int y)
{
	if(outOfBound(x,y) && fullCell(grid,x,y))
		return 1;
    return 0;
}

void Multiplayer()
{
	int x, y, winner = 0;
	int oldX, oldY;
	int cpt = 0;

	char grid[NB][NB];

	gridInitializer(grid);
	showGrid(grid);

	do
	{
		printf("\nJoueur 1");
		printf("\nEntrer une abscisse : ");
		scanf("%d", &x);

		printf("Entrer une ordonnee : ");
		scanf("%d", &y);
		printf("\n");

		if(validSpace(grid,oldX,oldY,x,y)){
			fillGrid(grid,x,y,CROSS);
			showGrid(grid);
		}

		else
		{
			while(!validSpace(grid,oldX,oldY,x,y))
			{
				printf("\nDeplacement invalide");
				printf("\nJoueur 1");
				printf("\nEntrer une abscisse : ");
				scanf("%d", &x);

				printf("Entrer une ordonnee : ");
				scanf("%d", &y);
				printf("\n");
			}
			fillGrid(grid,x,y,CROSS);
			showGrid(grid);
		}

		oldX = x;
		oldY = y;
		x=0; y=0; cpt++;

		if(cpt == 9){	//permet de tester le cas où la grille est complete
			if(chekLine(grid, oldX, oldY)){ //joueur 1 gagne avec une grille complete
				winner = 1;
				break;
			}
			else{
				break;
			}
		}

		if(!chekLine(grid, oldX, oldY)){
		printf("\nJoueur 2");
		printf("\nEntrer une abscisse : ");
		scanf("%d", &x);

		printf("Entrer une ordonnee : ");
		scanf("%d", &y);
		printf("\n");

		if(validSpace(grid,oldX,oldY,x,y)){
			fillGrid(grid,x,y,CIRCLE);
			showGrid(grid);
		}

		else
		{
			while(!validSpace(grid,oldX,oldY,x,y))
			{
				printf("\nDeplacement invalide");
				printf("\nJoueur 2");
				printf("\nEntrer une abscisse : ");
				scanf("%d", &x);

				printf("Entrer une ordonnee : ");
				scanf("%d", &y);
				printf("\n");
			}
			fillGrid(grid,x,y,CIRCLE);
			showGrid(grid);
		}

		oldX = x;
		oldY = y;
		x=0; y=0; cpt++;

		if(chekLine(grid, oldX, oldY))
		{
			winner = 2;
			break;
		}
	}
	else
	{
		winner = 1;
		break;
	}

	}while(cpt < 9 || winner !=0);
	if(winner == 0){
	    printf("Egalite\n\n");
	}
	else{
	    printf("Joueur %d a gagne.\n\n", winner);
	}
	exit(1);

}


void OnePlayer()
{
	int x, y, winner = 0;
	int cpt = 0;

	char grid[NB][NB];

	gridInitializer(grid);
	showGrid(grid);

	do
	{
		printf("\nJoueur 1");
		printf("\nEntrer une abscisse : ");
		scanf("%d", &x);

		printf("Entrer une ordonnee : ");
		scanf("%d", &y);
		printf("\n");

		if(validSpace(grid,x,y,x,y)){
			fillGrid(grid,x,y,CROSS);
			showGrid(grid);
		}

		else
		{
			while(!validSpace(grid,x,y,x,y))
			{
				printf("\nDeplacement invalide");
				printf("\nJoueur 1");
				printf("\nEntrer une abscisse : ");
				scanf("%d", &x);

				printf("Entrer une ordonnee : ");
				scanf("%d", &y);
				printf("\n");
			}
			fillGrid(grid,x,y,CROSS);
			showGrid(grid);
		}

		x=0; y=0; cpt++;

		if(Winner(grid) == 1){ //Winner() s'occupe de tester s'il y a un gagnant
            winner = 1;
            break;
        }

		if(cpt == 9)
            break;

		IA_play(grid,PROFONDEUR);

		cpt++;

        if(Winner(grid) == 2){ //Winner() s'occupe de tester s'il y a un gagnant
                winner = 2;
                break;
        }

	}while(winner != 0 || cpt < 9);

    if(winner == 0){
	    printf("Egalite\n\n");
	}
	else{
        printf("\nJoueur %d a gagne\n", winner);
	}
	exit(1);
}

int main(int argc, char **argv)
{
    srand(time(NULL));
	//Multiplayer();
	OnePlayer();

	return EXIT_SUCCESS;
}
