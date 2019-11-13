#include "../headers/printers.h"
#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<wchar.h>
#include<time.h>
#include<termios.h>
#include<stropts.h>
#include<locale.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>

#define PL L"\u03A8"
void print_gameboard(game_t gameBoard[][COLUMS],int *score, int *lifes)
{
	setlocale(LC_ALL, "");
	for(int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLUMS; j++) {
				printf("%ls", gameBoard[i][j]);
			}
		if(i == 5)
			printf("\t\tSCORE: %d", *score);
		if(i == 8)
			printf("\t\tLIVES: %d", *lifes);
		if(i == 7)
			printf("\t\tLEVEL: %d", *(score+1));
		if(i==9)
			printf("\t\tAMMO: %d", *(score+2));
		printf("\n");
	}
}

void print_spaceCraft(game_t gameBoard[][COLUMS], int *x, int *y){
	int posSpacecraft[2];
	setlocale(LC_ALL, "");
	gameBoard[*x][*y] = PL;
	posSpacecraft[0] = *x;
	posSpacecraft[1] = *y;
}
