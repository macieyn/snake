#include <stdio.h>
#include <stdlib.h>
// #include <windows.h> // for windows
#include <unistd.h> // for linux
#include "snake.h"


int main()
{
    printf("Hello SNAKE!\n\n");
    
    Snake snake;
    snake.length = 0;
    snake.body[0].x = 3, snake.body[0].y = 3;
    for (int i=1; i<10; i++) {
        snake.body[i].x = -1, snake.body[i].y = -1;
    }

    Food food;
    food.position[0].x = 1, food.position[0].y = 3; 
    food.position[1].x = 5, food.position[1].y = 3; 
    food.position[2].x = 1, food.position[2].y = 3; 
    food.position[3].x = 1, food.position[3].y = 0; 
    food.position[4].x = 1, food.position[4].y = 3; 

    int result = 0;
    int current_target = 0;
    int counter = 0;

    while (result == -1 || current_target < 5)
    {
        counter ++;
        // Sleep(500); // for windows
        // system("cls");
        
        usleep(500000); // for Unix
        system("clear");
        
        printf("COUNTER: %d\n", counter);

        printf("Welcome to SNAKE!\n");
        printf("Your score: %d\n", current_target);

        clear_display(screen);
        set_screen(&food, &snake, current_target);
        render_screen(screen);

        printf("\nSNAKE position: %i, %i\n", snake.body[0].x, snake.body[0].y);
        printf("FOOD position:  %i, %i\n", food.position[current_target].x, food.position[current_target].y);


        // -------- ABOVE OK - DON'T TOUCH -----------------------------------------------------------





        printf("\n# Food result: %d\n", result);

        update_tail(&snake);
        
        int sbx = snake.body[0].x, sby = snake.body[0].y;
        printf("\n$$$ Overlap UP:    \t%d\n", overlap_check(&snake, sbx-1, sby));
        printf("$$$ Overlap DOWN:  \t%d\n", overlap_check(&snake, sbx+1, sby));
        printf("$$$ Overlap RIGHT: \t%d\n", overlap_check(&snake, sbx, sby-1));
        printf("$$$ Overlap LEFT:  \t%d\n\n", overlap_check(&snake, sbx, sby+1));
        
        move_head(&snake, &food, current_target);
        printf("HEAD:\n%d, %d\n", snake.body[0].x, snake.body[0].y);
        
        result = food_reached(&snake, &food.position[current_target]);

        
        

        
        // -------- BELOW OK - DON'T TOUCH -----------------------------------------------------------
        
        // if (snake.body[0].x <= -1 || snake.body[0].x >= 8 || snake.body[0].y <= -1 || snake.body[0].y >= 8) break;
        print_tail_info(&snake);

        if (result == 1)
        {
            snake.length ++;
            current_target ++;
        }

        print_snake(&snake);
    }

    printf("The END!");

    return 0;
}
