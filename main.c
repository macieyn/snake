#include <stdio.h>
#include <stdlib.h>
// #include <windows.h> // for windows
#include <unistd.h> // for linux


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


struct Coord {
    int x;
    int y;
};


struct Snake {
    int tail_length;  
    struct Coord tail[10];
    char dir;
};

void print_snake(struct Snake *snake)
{
    int head_x = snake->tail[0].x;
    int head_y = snake->tail[0].y;
    int length = snake->tail_length;
    printf("\nSnake:\n--------------\nX: %d\nY: %d\nLen: %d\n", head_x, head_y, length);
}

void update_tail(struct Snake *snake) {
    for(int i=snake->tail_length; i>0; i--) {
        snake->tail[i] = snake->tail[i-1];
    }
};

struct Food {
    struct Coord position;
};


void clear_display(char display[])
{
    for (int i=0 ; i<8; i++) display[i] = 0b0;
}

int go_to_point(struct Food food[], struct Snake *snake, int current_target)
{
    // TODO: Sprawdzić czy wąż nie wchodzi na siebie

    int result = 0;

    // sprawdzam czy punkt został osiągnięty
    if (food[current_target].position.x == snake->tail[0].x && food[current_target].position.y == snake->tail[0].y){
        snake->tail_length ++;
        current_target ++; 
        printf("\nFood!\n");
        result = 1;
    }

    // ustawiam kierunek ruchu
    if (food[current_target].position.x > snake->tail[0].x){
        snake->tail[0].x ++;
        // snake->dir = 'r';
    }
    else if (food->position.x < snake->tail[0].x){
        snake->tail[0].x --;
        // snake->dir = 'l';
    }
    else if (food->position.y > snake->tail[0].y){
        snake->tail[0].y ++;
        // snake->dir = 'u';
    }
    else if (food->position.y < snake->tail[0].y){
        snake->tail[0].y --;
        // snake->dir = 'd';
    }
    // else {
    //     if (snake->dir == 'u') snake->tail[0].y ++;
    //     if (snake->dir == 'd') snake->tail[0].y --;
    //     if (snake->dir == 'l') snake->tail[0].x --;
    //     if (snake->dir == 'r') snake->tail[0].x ++;
    // }

    return result;
}

void render_screen(char my_screen[])
{
    printf("\n----------------\n");
    for (int i=0; i<8; i++)
    {
        for (int j=7; j>=0; j--)
        {
            if (my_screen[i] & (1 << j)) printf(" *");
            else printf("  ");
        }
        printf("\n");
    }
    printf("----------------\n");
}

void set_screen(struct Food food[], struct Snake *snake, int current_target)
{
    for (int i=0; i<8; i++)
    {
        for (int j=7; j>=0; j--)
        {   
            if (food[current_target].position.x == i && food[current_target].position.y == j)
            {
                    char row = screen[i];
                    row = 1 << j;
                    screen[i] |= row; 
            }

            for (int k=0; k<10; k++)
            {
                if (snake->tail[k].x == i && snake->tail[k].y == j)
                {
                    char row = screen[i];
                    row = 1 << j;
                    screen[i] |= row; 
                }
            }
        }
    }
}

void print_tail(struct Snake *snake)
{
    for (int i=0; i<10; i++) {
        printf("X: %d, Y: %d\n", snake->tail[i].x, snake->tail[i].y); 
    }
}

int main()
{
    printf("Hello SNAKE!\n\n");
    struct Coord init[10] = { {3, 3}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    struct Snake snake = {0, *init, 'd'};
    struct Food food[5];

    int result = 0;
    for (int i=0; i<5; i++)
    {
        food[i].position.x = rand() % 8;
        food[i].position.y = rand() % 8;
    }

    int current_target = 0;

    while (result == -1 || current_target < 5)
    {
        // Sleep(1000); // for windows
        // system("cls");
        
        usleep(500000); // for Unix
        system("clear");
        
        printf("Welcome to SNAKE!\n");
        printf("Your score: %d", current_target);

        clear_display(screen);
        set_screen(food, &snake, current_target);
        render_screen(screen);

        printf("Snake position: %i, %i\n", snake.tail[0].x, snake.tail[0].y);
        printf("Point position: %i, %i\n", food[current_target].position.x, food[current_target].position.y);

        print_tail(&snake);

        update_tail(&snake);

        result = go_to_point(food, &snake, current_target);

        if (snake.tail[0].x <= -1 || snake.tail[0].x >= 8 || snake.tail[0].y <= -1 || snake.tail[0].y >= 8) break;

        if (result == 1)
        {
            snake.tail_length ++;
            current_target ++;
        }

        print_snake(&snake);
    }

    printf("The END!");

    return 0;
}
