#include <cs50.h>
#include <stdio.h>

void pyramid(int h);
int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    pyramid(n);
}

void pyramid(int h)
{
    for (int i = 1; i <= h; i++)
    {
        for (int j = 0; j < (h - i); j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
