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
    0b00000000,
};

struct Snake
{
    int x;
    int y;
    int tail;
};

struct Point {
    int x;
    int y;
};

void clear_display(char display[], int size)
{
    for (int i=0 ; i<size; i++) display[i] = 0b0;
}

int go_to_point(struct Point *point, struct Snake *snake)
{
    if (point->x == snake->x && point->y == snake->y) return 1; 
    if (point->x > snake->x) snake->x ++;
    else if (point->x < snake->x) snake->x --;
    else if (point->y > snake->y) snake->y ++;
    else if (point->y < snake->y) snake->y --;
    return 0;
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

int main()
{
    printf("Hello SNAKE!\n\n");
    struct Snake snake = {3, 3, 0};
    struct Point points[5];

    int result = 0;
    for (int i=0; i<5; i++)
    {
        points[i].x = rand() % 8;
        points[i].y = rand() % 8;
    }

    int current_point = 0;

    while (result == -1 || current_point < 5)
    {
        
        if (snake.x <= -1 || snake.x >= 8 || snake.y <= -1 || snake.y >= 8) result = -1;
        // Sleep(1000); // for windows
        usleep(500000); // for Unix
        system("clear");
        printf("Welcome to SNAKE!\n");
        printf("Your score: %d", current_point);

        clear_display(screen, 8);

        for (int i=0; i<8; i++)
        {
            for (int j=7; j>=0; j--)
            {   
                if (points[current_point].x == i && points[current_point].y == j)
                {
                        char row = screen[i];
                        row = 1 << j;
                        screen[i] |= row; 
                }
                
                if (snake.x == i && snake.y == j)
                {
                        char row = screen[i];
                        row = 1 << j;
                        screen[i] |= row; 
                }
            }
        }

        render_screen(screen);

        printf("Snake position: %i, %i\n", snake.x, snake.y);
        printf("Point position: %i, %i\n", points[current_point].x, points[current_point].y);

        result = go_to_point(&points[current_point], &snake);
        if (result == 1)
        {
            snake.tail ++;
            current_point ++;
        }
    }

    printf("The END!");

    return 0;
}
