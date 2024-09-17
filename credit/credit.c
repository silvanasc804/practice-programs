#include <cs50.h>
#include <stdio.h>

int checksum(long n);
int first_two(long n);
int length(long n);

int main(void)
{
    long number = get_long("Number :");
    if ((checksum(number) % 10) == 0)
    {
        int len = length(number);
        int first = first_two(number);
        if (len == 15 && (first == 34 || first == 37))
        {
            printf("AMEX\n");
        }
        else if (len == 16 && (first >= 51 && first <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((len == 13 || len == 16) && (first / 10) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int first_two(long n)
{
    while (n > 99)
    {
        n /= 10;
    }
    return (int) n;
}

int length(long n)
{
    int l = 1;
    while (n > 10)
    {
        n /= 10;
        l += 1;
    }
    return l;
}

int checksum(long n)
{
    long nm; // not multiplied
    long m;  // multiplied
    int sum = 0;
    while (n > 0)
    {
        // Digits that weren´t multiplied by 2 (starting with the number’s second-to-last)
        nm = n % 10;
        n = n / 10;
        // Multiply by two the other numbers
        if (n > 0)
        {
            m = (n % 10) * 2;
            if (m >= 10)
            {
                // add m's digits if there are 2
                m = 1 + (m % 10);
            }
        }
        else
        {
            m = 0;
        }
        n = n / 10;
        // Since the order does not matter in addition, we can add in each loop.
        sum += nm + m;
    }

    return sum;
}
