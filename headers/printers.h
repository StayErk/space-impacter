#define game_t int*
#define ROWS 47
#define COLUMS 34

void print_gameboard(game_t gameboard[][COLUMS], int *score, int *lifes);
void print_spaceCraft(game_t gameboard[][COLUMS], int *x_axis, int *y_axis);
void print_asteroid(int x_axis, int y_axis);
void print_projectile(int x_axis, int y_axis);
