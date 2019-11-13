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
#include"printers.h"
#include"queue.h"
/*unsigned char gameStarter(char *playerName);
unsigned char isDead(int *posSpacecraft, int *posAsteroid);
unsigned char checkBorder(int *posSpacecraft);
unsigned char projectileHit(int *posProjectile)

//function to fire and update projectile position on the game board
int *posProjectile fire(int *posSpacecraft);
void updateProjectilePos(int *posProjectile);

// functions to generate and update asteroids
int *posAsteroid generateAsteroid();
void moveAsteroid(int *posAsteroid);

// functions to generate and move spacecraft
*/
int *move_spaceCraft(game_t gameBoard[][COLUMS], int *x_pos, int *y_pos, int *lives);
int updateProjectile(game_t gameBoard[][COLUMS]);
void spawnAsteroid(game_t gameBoard[][COLUMS]);
void spawnAmmo(game_t gameBoard[][COLUMS]);
void initGame();
