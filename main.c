#include <stdio.h>
#include <stdlib.h>
// #include <windows.h> // for windows
#include <unistd.h> // for linux
#include "snake.h"

char get_button();

int main()
{
    Snake snake;
    snake.length = 0;
    snake.direction = UP;
    snake.body[0].x = 3, snake.body[0].y = 3;
    for (int i=1; i<(sizeof(snake.body)/sizeof(snake.body[0])); i++) {
        snake.body[i].x = -1, snake.body[i].y = -1;
    }

    Coord food;
    random_food(&food);

    int result = 0;

    while (result != -1)
    {
        usleep(500000); // for Unix
        system("clear");

        clear_display(screen);
        set_screen(&food, &snake);
        render_screen(screen);

        change_direction(&snake, get_button());

        update_tail(&snake);

        result = move_head(&snake); // overlap check 
        if (result == -1) {
            break;
        }

        result = food_reached(&snake, &food); // hungry?
        if (result == 1)
        {
            snake.length ++;
            random_food(&food);
        }

        result = wall_hit(&snake);
    }

    return 0;
}
