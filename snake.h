#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdio.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct Snake {
    int length;  
    Coord body[64];
    char direction;
} Snake; 

int  change_direction(Snake *snake, char direction);
void clear_display(char display[]);
int  food_reached(Snake *snake, Coord *food);
int  move_head(Snake *snake);
int  overlap_check(Snake *snake);
void random_food(Coord *food);
void render_screen(char my_screen[]);
void set_screen(Coord *food, Snake *snake);
void update_tail(Snake *snake);
int  wall_hit(Snake *snake);

char screen[8];

#endif // SNAKE_H_