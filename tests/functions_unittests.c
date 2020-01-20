#include "functions_unittests.h"
#include "../snake.h"

// Test sprawdza czy miejsce jest wolne
// Jeśli wolne zwraca 1, jeśli nie zwraca 0
int test_check_if_not_overlapping_positive()
{
    int result = 0;

    Snake snake;
    snake.length = 10;
    snake.body[0].x = 3, snake.body[0].y = 3;

    if (check_if_not_overlapping(&snake, 3, 2) == 1) result = 1;

    return result; 
}

// Test sprawdza czy miejsce jest zajęte 
// Jeśli zajęte zwraca 1, jeśli nie zwraca 0
int test_check_if_not_overlapping_negative()
{
    int result = 0;
    Snake snake;
    snake.length = 10;
    snake.body[0].x = 3, snake.body[0].y = 3; 
    snake.body[1].x = 3, snake.body[1].y = 2;

    // printf("#: %d\n", check_if_empty_space(&snake, 3, 2));

    if (check_if_not_overlapping(&snake, 3, 2) != 1) result = 1;

    return result; 
}

// Test sprawdza czy kolejne pozycje są poprawnie aktualizowane
int test_update_tail()
{
    int result = 1;

    Snake snake;
    snake.length = 10;
    snake.body[0].x = 3, snake.body[0].y = 3;
    for (int i=1; i<snake.length; i++) {
        snake.body[i].x = -1, snake.body[i].y = -1;
    }
    
    Coord expected[10] = {{3, 3}, {3, 3}, {-1, -1},  {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};

    int body_elements = sizeof(snake.body) / sizeof(snake.body[0]);

    update_tail(&snake);
    update_tail(&snake);
    update_tail(&snake);
    update_tail(&snake);

    for (int i=0; i<body_elements; i++) {
        // printf("%d=%d %d=%d\n", snake.body[i].x, expected[i].x, snake.body[i].y, expected[i].y);
        if (snake.body[i].x != expected[i].x || snake.body[i].y != expected[i].y) result = 0; 
    }

    return result;
}

// Test sprawdzający czy głowa węża znajduje się z pozycji pokarmu
int test_food_reached_positive()
{
    int result = 1;

    Coord init[10] = { {3, 3}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    Snake snake = {1, *init};
    Coord food = {3, 3};

    int snake_fed = food_reached(&snake, &food);
    if (snake_fed != 1) result = 0;

    return result;
}

// Test sprawdzający czy głowa węża nie znajduje się z pozycji pokarmu
int test_food_reached_negative()
{
    int result = 1;

    Coord init[10] = { {3, 3}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    Snake snake = {1, *init};
    Coord food = {3, 2};

    int snake_fed = food_reached(&snake, &food);
    if (snake_fed == 1) result = 0;

    return result;
}