#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = 50;
    int *p = &n; //Gets memory location (pointer) of n &n = memory location of, *p = pointer
    printf("%i\n", *p); //Notice that the printf line prints the integer at the location of p

    string s = "HI!";
    printf("%p\n", s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);

    char *c = "HI!";
    printf("%s\n", c);

    char *c1 = "HI!";
    printf("%c\n", c1[0]);
    printf("%c\n", c1[1]);
    printf("%c\n", c1[2]);

    char *c2 = "HI!";
    printf("%c\n", *c2);
    printf("%c\n", *(c2 + 1));
    printf("%c\n", *(c2 + 2));
}