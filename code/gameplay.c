#include"../headers/gameplay.h"
#include"../headers/printers.h"

#define PL L"\u03A8"
#define BK L"\u2800"
#define BU L"\u02c4"
#define VB L"\u2503"
#define AS L"\u03a6"
#define HB L"\u2501"
#define AM L"\u03b1"
int   flag=0, spawn_rate =28, i=0, level=1, ammo_avaiable=25;
Queue projectiles, asteroids, ammo;
struct termios saved_attributes;
int *posizione_temp;



void moveRight(game_t gameBoard[][COLUMS], int *x, int *y);
void moveLeft(game_t gameBoard[][COLUMS], int *x, int *y);
void fireProjectile(game_t gameBoard[][COLUMS], int *x, int *y);
int updateAsteroids(game_t gameBoard[][COLUMS], int *lives);
void updateAmmo(game_t gameBoard[][COLUMS]);
void damage(int *lifes);

void initGame()
{
	srand(time(NULL));
	posizione_temp = malloc(sizeof(int) *2);
	projectiles = newQueue();
	asteroids = newQueue();
	ammo = newQueue();
}

void spawnAsteroid(game_t gameBoard[][COLUMS])
{
	int x_pos, y_pos;
	if(flag%spawn_rate == 1){
	//	printf("SpawnRate= 1/%d", spawn_rate);
	//	printf("spawnAsteroid\n");
		x_pos = rand() % (COLUMS-2)+1;
		y_pos = 1;
		gameBoard[y_pos][x_pos] = AS;
		*posizione_temp = y_pos;
		*(posizione_temp+1) = x_pos;
		if(enqueue(asteroids, posizione_temp) == 0) printf("Errore queue\n");
		i++;
		if(i == 4)
		{
			if(spawn_rate != 2)
				spawn_rate--;
			i=0;
			level++;
		}
	}
	flag++;
}

void spawnAmmo(game_t gameBoard[][COLUMS])
{
	int x_pos, y_pos;
	if((rand()+ammo_avaiable*spawn_rate)%spawn_rate == 1){
	//	printf("SpawnRate= 1/%d", spawn_rate);
	//	printf("spawnAsteroid\n");
		x_pos = rand() % (COLUMS-2)+1;
		y_pos = 1;
		gameBoard[y_pos][x_pos] = AM;
		*posizione_temp = y_pos;
		*(posizione_temp+1) = x_pos;
		if(enqueue(ammo, posizione_temp) == 0) printf("Errore queue\n");
	}
}

int updateAsteroids(game_t gameBoard[][COLUMS], int *lives){
	Queue temp;
	temp = newQueue();
	int points=0;
	//printf("UpdateAsteroid\n");
	while (!isEmptyQueue(asteroids)){
		posizione_temp = dequeue(asteroids);
		//printf("Posizione Asteroide: %d", *(posizione_temp));
		if(*(posizione_temp) == 45){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			damage(lives);
		}
		else if(gameBoard[*posizione_temp][*(posizione_temp+1)] == PL){
			exit(0);
		}
		else if(!(gameBoard[*posizione_temp][*(posizione_temp+1)] == BU)){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			gameBoard[(*posizione_temp)+1][*(posizione_temp+1)] = AS;
			*posizione_temp += 1;
			enqueue(temp, posizione_temp);
		}
		else if ((gameBoard[(*posizione_temp)+1][*(posizione_temp+1)] == BU)){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			points = 100;
		}
		else if ((gameBoard[(*posizione_temp)][*(posizione_temp+1)] == BU)){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			points = 100;
		}
		else if ((gameBoard[(*posizione_temp)-1][*(posizione_temp+1)] == BU)){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			points=100;
		}
	}
	asteroids = temp;
	return points;
}

void updateAmmo(game_t gameBoard[][COLUMS]){
	Queue temp;
	temp = newQueue();
	//printf("UpdateAsteroid\n");
	while (!isEmptyQueue(ammo)){
		posizione_temp = dequeue(ammo);
		//printf("Posizione Asteroide: %d", *(posizione_temp));
		if(*(posizione_temp) == 45){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
		}
		else if(!(gameBoard[*posizione_temp][*(posizione_temp+1)] == BU)){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			gameBoard[(*posizione_temp)+1][*(posizione_temp+1)] = AM;
			*posizione_temp += 1;
			enqueue(temp, posizione_temp);
		}
		else if ((gameBoard[(*posizione_temp)+1][*(posizione_temp+1)] == BU)){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			ammo_avaiable+= 25;
		}
		else if ((gameBoard[(*posizione_temp)][*(posizione_temp+1)] == BU)){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			ammo_avaiable += 25;
		}
		else if ((gameBoard[(*posizione_temp)-1][*(posizione_temp+1)] == BU)){
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			ammo_avaiable += 25;
		}
	}
	ammo = temp;
}

int *move_spaceCraft(game_t gameBoard[][COLUMS], int *x, int* y, int *lives){
	char c, mv='s';
	int *statistics=malloc(sizeof(int) * 3);
	read(0, &c, 1);
	if(c == 'a' || c == 'd' || c == 'm')
		mv = c;
	if (*lives == 0)
		exit(1);
	if (!isEmptyQueue(asteroids))
		*statistics += updateAsteroids(gameBoard, lives);
	if (!isEmptyQueue(projectiles))
		*statistics += updateProjectile(gameBoard);
	if (!isEmptyQueue(ammo))
		updateAmmo(gameBoard);

	switch(mv){
		case 'a':
			moveLeft(gameBoard, y, x);
			break;
		case 'd':
			moveRight(gameBoard, y, x);
			break;
		case 'm':
			fireProjectile(gameBoard, y, x);
			break;
	}
	(*statistics) += 1;
	*(statistics+1) = level;
	*(statistics+2) = ammo_avaiable;

	return statistics;
}

void moveLeft(game_t gameBoard[][COLUMS], int *y, int *x){
   	int c = *gameBoard[*x][(*y)-1];	
	if(c == *VB)
		return ;
	gameBoard[*x][*y] = BK;
	(*y)--;
	gameBoard[*x][*y] = PL;
}

void damage(int *lifes)
{
	(*lifes)--;
}

void moveRight(game_t gameBoard[][COLUMS], int *y, int *x){
 	int c = *gameBoard[*x][(*y)+1];
	if(c == *VB)
		return ;
    if((gameBoard[*x][(*y)+1]) == VB)
	   return ;   
	gameBoard[*x][*y] = BK;
	(*y)++;
	gameBoard[*x][*y] = PL;
}

void fireProjectile(game_t gameBoard[][COLUMS], int*y, int*x){
	//printf("fireProjectile\n");
	if(ammo_avaiable > 0){	
		*posizione_temp = *x-1;
		*(posizione_temp+1) = *y;
		gameBoard[*x-1][*y] = BU;
		if(enqueue(projectiles, posizione_temp) == 0) printf("Errore enqueue proiettili\n");
		ammo_avaiable--;
	}
}



int updateProjectile(game_t gameBoard[][COLUMS]){
	int points;
	Queue temp = newQueue();
	//printf("Updateprojectile\n");
	//printf("posizione proiettile prima del for: %d, %d\n", posProjectile[0], posProjectile[1]);
	while (!isEmptyQueue(projectiles))
	{
		posizione_temp = dequeue(projectiles);
		//printf("POSIZIONE PROIETTILE: %d", *posizione_temp);
		if (*posizione_temp == 23){
		//	printf("\t23");
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
		}
		else if(!(gameBoard[(*posizione_temp)][*(posizione_temp+1)] == AS))
		{
			gameBoard[*posizione_temp][*(posizione_temp+1)] = BK;
			gameBoard[(*posizione_temp)-1][*(posizione_temp+1)] = BU;
			*posizione_temp -= 1;
			enqueue(temp, posizione_temp);
		}
		else ;
	}
	projectiles = temp;
	return points;
}
// Take a player name and return true if ok.
/*unsigned char gameStart(char *playerName)
{
	if (scanf("%s", playerName) > 0)
	{
			fflush();
			return TRUE;
	}
	else return FALSE;
}

unsigned char isDead(int *posSpacecraft, int *posAsteroid)
{
	if (posSpacecraft[0] == posAsteroid[0] && posSpacecraft[1] == posAsteroid[1])
		return TRUE;
	else return FALSE;
}

int *posProjectile fire(int *posSpacecraft)
{
	int posProjectile[2];
	posProjectile[0] = posSpacecraft[0];
    posProjectile[1] = posSpacecraft[1]+1;
	if(!projectileHit(posProjectile))
		print_projectile(posSpacecraft[0], posSpacecraft[1]+1);
	else damageAsteroid();
}

void updateProjectilePos(int *posProjectile)
{
	if (!projectileHit(posProjectile))
		print_projectile(posSpacecraft[0], posSpacecraft[1]+1);
	else damageAsteroid();

	if (posProjectile[1] == ROWS-2) destroyProjectile();
}

int *posAsteroid generateAsteroid()
{
	int posAsteroid[2];
	// TO-DO create randomizer
	posAsteroid[0] = rand() % COLUMS;
   	posAsteroid[1] = ROWS-1;
	return posAsteroid;
}

void moveAsteroid(int *posAsteroid)
{
	posAsteroid[1]--;
}*/		
