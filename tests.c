#include <stdio.h>
#include <stdlib.h>
#include "./tests/functions_unittests.h"


int main()
{
    int result = 1;
    printf("INITIAL TEST: \t\t\t\t\t%d\n", result);

    result = test_check_if_not_overlapping_positive();
    printf("TEST OVERLAP POS: \t\t\t\t%d\n", result);

    result = test_check_if_not_overlapping_negative();
    printf("TEST OVERLAP NEG: \t\t\t\t%d\n", result);

    result = test_update_tail();
    printf("TEST TAIL UPDATE: \t\t\t\t%d\n", result);

    result = test_food_reached_positive();
    printf("TEST FOOD REACHED POS: \t\t\t\t%d\n", result);

    result = test_food_reached_negative();
    printf("TEST FOOD REACHED NEG: \t\t\t\t%d\n", result);

    return 0;
}
