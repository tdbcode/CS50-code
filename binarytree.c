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

void free_tree(leaf *root);

int main(void)
{
    leaf *root = NULL; // Create root of tree

    leaf *l = malloc(sizeof(leaf));
    if (l == NULL)
    {
        return 1;
    }

    int no1 = get_int("Enter your first number");

    // Create root of tree
    l->number = no1;
    l->left = NULL;
    l->right = NULL;

    root = l;

    int no2 = get_int("How many items do you want to add to the tree?");
    leaf *temp = NULL; // Temp leaf
    temp = root;
    for (int i = 0; i < no2; i++)
    {
        l = malloc(sizeof(leaf));
        if (l == NULL)
        {
            free_tree();
        }

        no1 = get_int("Enter your next number");
        l->number = no1;

        if (l->number > temp = root->number)
        {
            temp->right = l;
        }
        else
        {
            temp->left = l;
        }
    }
}

void free_tree(leaf *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        return 0;
    }
    else
        leaf *current = root->left;



}