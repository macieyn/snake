#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdio.h>

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct Food {
    Coord position[5];
} Food;

typedef struct Snake {
    int length;  
    Coord body[10];
    char direction;
} Snake; 

int check_if_not_overlapping(Snake *snake, int x, int y);
void clear_display(char display[]);
int food_reached(Snake *snake, Coord *food);
int move_head(Snake *snake, Food food[], int current_target);
int overlap_check(Snake *snake, int x, int y);
void print_snake(Snake *snake);
void print_tail_info(Snake *snake);
void render_screen(char my_screen[]);
void set_screen(Food food[], Snake *snake, int current_target);
void update_tail(Snake *snake);

char screen[8];

#endif // SNAKE_H_