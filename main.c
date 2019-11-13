/*
 * main.c
 * Copyright (C) 2019 andreaerk <andreaerk@pop-os>
 *
 * Distributed under terms of the MIT license.
 */
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
#include"headers/printers.h"
#include"headers/gameplay.h"
//#include"menu.h"

#define game_t int*
// Dimension of game board

// ASCII code for | and -
#define VB L"\u2503"
#define HB L"\u2501"
#define BK L"\u2800"
#define PL L"\u03A8"
#define UL L"\u250f"
#define UR L"\u2513"
#define BR L"\u251b"
#define BL L"\u2517"

// ASCII code for wasd.
#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97

struct termios saved_attributes;

void input_mode();
void reset_input_mode();


int main (void)
{
	setlocale(LC_ALL, "");
	char *playerName, c;
	int *statistics, *temp,lifes=5;
	unsigned char startGame = 0;
	int x_pos = 44, y_pos = 17;

	statistics = malloc(sizeof(int) *3);
	temp = malloc(sizeof(int) * 3);
	fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, O_NONBLOCK);

	game_t gameBoard[ROWS][COLUMS]={
	{UL, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, UR},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{VB, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK,BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, VB},
	{BL, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, HB, BR},
};
	print_spaceCraft(gameBoard, &x_pos, &y_pos);
	print_gameboard(gameBoard, statistics, &lifes);
	
	input_mode();
	initGame();
	while(1)
	{
		spawnAsteroid(gameBoard);
		spawnAmmo(gameBoard);	
	  	system("clear");
//		printf("Ho letto\n");
		temp = move_spaceCraft(gameBoard, &x_pos, &y_pos, &lifes); 
		*statistics += *temp;
		*(statistics+1) = *(temp+1);
		*(statistics+2) = *(temp+2);
	//	print_spaceCraft(gameBoard, &x_pos, &y_pos);
		print_gameboard(gameBoard, statistics, &lifes);
		usleep(105000);
	}
	reset_input_mode();
	return 0;
}

void input_mode()
{
	struct termios tattr;
	char *name;

	/* Make sure stdin is a terminal. */
	if (!isatty (STDIN_FILENO))	{
   		fprintf (stderr, "Not a terminal.\n");
   		 exit (EXIT_FAILURE);
 	 }

	/* Save the terminal attributes so we can restore them later. */
	tcgetattr (STDIN_FILENO, &saved_attributes);
	atexit (reset_input_mode);

	/* Set the funny terminal modes. */
	tcgetattr (STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO|O_NONBLOCK); /* Clear ICANON and ECHO. */
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

void reset_input_mode(){
	tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}

