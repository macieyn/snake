#include "snake.h"

char screen[8] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b0000000,
};


void print_snake(Snake *snake){
    int head_x = snake->body[0].x;
    int head_y = snake->body[0].y;
    int length = snake->length;
    printf("\nSnake:\n--------------\nX: %d\nY: %d\nLen: %d\n", head_x, head_y, length);
};

// Ta funkcja ma za zadanie zaktualizować pozycje ogona po przesunięciu głowy
// kolejne elementy przyjmują wartości, elementu je poprzedzającego
void update_tail(Snake *snake) {
    printf("Tail:\n-----------------\n");
    for(int i=snake->length; i>0; i--) {
        snake->body[i].x = snake->body[i-1].x;
        snake->body[i].y = snake->body[i-1].y;
        printf("%d, %d\n", snake->body[i].x, snake->body[i].y);
    }
    printf("-----------------\n");
};


void clear_display(char display[]){
    for (int i=0 ; i<8; i++) display[i] = 0b0;
};

// Sprawdza czy sam na siebie nie wchodzi
int check_if_not_overlapping(Snake *snake, int x, int y){   
    int result = 1;
    for (int i=0; i<snake->length; i++) {
        // printf("%d %d %d %d\n", snake->body[i].x, x, snake->body[i].y, y);
        if(snake->body[i].x == x && snake->body[i].y == y) result = 0;
    }
    return result;
};


int overlap_check(Snake *snake, int x, int y) {
    for (int i=0; i<10; i++) {
        if (snake->body[i].x == x && snake->body[i].y == y) {
            return 1;
        }
    }
    return 0;
}


// AUTOPILOT FUNCTION - needed??? Only for testing... So, yeah...
int move_head(Snake *snake, Food *food, int current_target){
    int result = 0;
    int sbx = snake->body[0].x, sby = snake->body[0].y;
    int fpx = food->position[current_target].x, fpy = food->position[current_target].y;

    if ((sbx > fpx) && (overlap_check(snake, sbx-1, sby) == 0)) {
        snake->body[0].x --;
        printf("UP\n");
    }
    else if ((sbx < fpx) && (overlap_check(snake, sbx+1, sby) == 0)) {
        snake->body[0].x ++;
        printf("DOWN\n");
    }
    else if ((sby > fpy) && (overlap_check(snake, sbx, sby-1) == 0)) {
        snake->body[0].y --;
        printf("LEFT\n");
    } 
    else if ((sby < fpy) && (overlap_check(snake, sbx, sby+1) == 0)) {
        snake->body[0].y ++;
        printf("RIGHT\n");
    } 
    

    return result;
};


void render_screen(char my_screen[]){
    printf("\n----------------\n");
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (my_screen[i] & (1 << j)) printf(" *");
            else printf("  ");
        }
        printf("\n");
    }
    printf("----------------\n");
};


void set_screen(Food *food, Snake *snake, int current_target){
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {   
            if (food->position[current_target].x == i && food->position[current_target].y == j)
            {
                    char row = screen[i];
                    row = 1 << j;
                    screen[i] |= row; 
            }

            for (int k=0; k<10; k++)
            {
                if (snake->body[k].x == i && snake->body[k].y == j)
                {
                    char row = screen[i];
                    row = 1 << j;
                    screen[i] |= row; 
                }
            }
        }
    }
};


void print_tail_info(Snake *snake){
    for (int i=0; i<10; i++) {
        printf("#%d X: %d, Y: %d\n", i, snake->body[i].x, snake->body[i].y); 
    }
};


int food_reached(Snake *snake, Coord *food){
    int result = 0;
    
    for (int i=0; i<snake->length+1; i++) {
        if(snake->body[i].x == food->x && snake->body[i].y == food->y) result = 1;
        // else printf("%d", i);
    }   

    return result;
}