#include <stdio.h>
#include <stdlib.h>

// Define a leaf
typedef struc leaf
{
    int number;
    struct leaf *left;
    struct leaf *right;
}
leaf;

int main(void)
{
    node *root = NULL; // First node

    leaf *l = malloc(sizeof(leaf));
    if (l == NULL)
    {
        return 1;
    }

    // Create root of tre
}