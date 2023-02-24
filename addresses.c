#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n; //Gets memory location (pointer) of n &n = memory location of, *p = pointer
    printf("%p\n", p);
}