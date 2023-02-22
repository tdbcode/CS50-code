#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int pop_start_size = 0;
    int pop_end_size = 0;
    int population = 0;
    while (pop_start_size < 9)
    {
        pop_start_size = get_int("Start size: ");
    }

    // TODO: Prompt for end size


    while (pop_end_size < pop_start_size)
    {
        pop_end_size = get_int("End size: ");
    }

    // TODO: Calculate number of years until we reach threshold
    population = pop_start_size;
    int popincrease = 0;
    int popdecrease = 0;
    int years = 0;
    while (population < pop_end_size)
    {
        popincrease = population / 3;
        popdecrease = population / 4;

        population = population + popincrease - popdecrease;
        years++;
    }


    // TODO: Print number of years
    printf("Years: %i\n", years);
}
