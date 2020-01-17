#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

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
};

int main()
{
    printf("Hello world!\n");
    struct Snake snake = {3, 3};
    char dir = 'w';

    while (1)
    {
        printf("----------------\n");
        for (int i=0; i<8; i++)
        {
            for (int j=7; j>=0; j--)
            {
                if (snake.x == i && snake.y == j) printf(" *");
                else if (screen[i] & (1 << j)) printf(" *");
                else printf("  ");
            }
            printf("\n");
        }
        printf("----------------\n");
/*
        if(kbhit()){
            dir = getch();
        }
*/
        if(_kbhit()) dir = _getch();
        switch(dir) { // the real value
            case 'd':
                snake.y --;
                break;
            case 'w':
                snake.x --;
                break;
            case 's':
                snake.x ++;
                break;
            case 'a':
                snake.y ++;
                break;
        }
        Sleep(1000);
    }

    return 0;
}
