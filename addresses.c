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
}