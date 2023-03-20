#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// Define a leaf
typedef struct leaf
{
    int number;
    struct leaf *left;
    struct leaf *right;
}
leaf;

void free_tree(leaf *root);
void print_tree(leaf *root);

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
    bool placed = false;
    for (int i = 0; i < no2; i++)
    {
        l = malloc(sizeof(leaf));
        if (l == NULL)
        {
            free_tree(root);
            return 1;
        }

        no1 = get_int("Enter your next number");
        l->number = no1;
        l->left = NULL;
        l->right = NULL;

        temp = root;

        while (placed == false)
        {
            if (l->number > temp->number)
            {
                if (temp->right == NULL)
                {
                    temp->right = l;
                    printf("%i\n added to the right", temp->number);
                }
                else
                {
                    temp->right = temp->right->right;
                }

            }
            else
            {
                if (temp->left == NULL)
                {
                    temp->left = l;
                    printf("%i\n added to the left", temp->number);
                }
                else
                {
                    temp->left = temp->left->left;
                }
            }

        }

    }
}

void free_tree(leaf *root)
{
    if (root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print_tree(leaf *root)
{
    if (root == NULL)
    {
        return;
    }

    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}