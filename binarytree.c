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
bool search(leaf *tree, int number);

int main(void)
{
    leaf *root = NULL; // Create root of tree

    leaf *l = malloc(sizeof(leaf)); // Assign memory for new leaf
    // If memory not allocated free memory and exit program
    if (l == NULL)
    {
        return 1;
    }

    int no1 = get_int("Enter your first number\n");

    // Create root of tree
    l->number = no1;
    l->left = NULL;
    l->right = NULL;

    root = l; // Set root to new leaf

    // Ask how many items the user wants to add to tree
    int no2 = get_int("How many items do you want to add to the tree?\n");
    leaf *temp = NULL; // Create a temporary leaf for story
    temp = root; // Set temp to root of tree
    bool placed = false; // Set leaf placed as false

    // Start loop for as many items as the user wants to add
    for (int i = 0; i < no2; i++)
    {
        l = malloc(sizeof(leaf)); // Assign memory for new leaf
        // If memory not allocated free memory and exit program
        if (l == NULL)
        {
            free_tree(root);
            return 1;
        }

        // Ask user to enter next number
        no1 = get_int("Enter your next number\n");

        // Assign values to leaf
        l->number = no1;
        l->left = NULL;
        l->right = NULL;

        // Set placed as false;
        placed = false;

        // While leaf isn't placed, find location within tree
        while (placed == false)
        {
            // If new number is more than current leaf, try assign to right
            if (l->number > temp->number)
            {
                // Check if current leaf pointer to the right is empty
                if (temp->right == NULL)
                {
                    temp->right = l; // if so assign the new leaf there
                    // Output that it was added
                    printf("%i added to the right\n", temp->number);
                    placed = true; // updated placed to true
                }
                else
                {
                    // Else update current pointer
                    temp = temp->right;
                }
            }
            // Else, number is more than current leaf, try assign to right
            else
            {
                // Check if current leaf pointer to the right is empty
                if (temp->left == NULL)
                {
                    temp->left = l; // if so assign the new leaf there
                    // Output that it was added
                    printf("%i added to the left\n", temp->number);
                    placed = true; // updated placed to true
                }
                else
                {
                    // Else update current pointer
                    temp = temp->left;
                }
            }

            // Print tree
            print_tree(root);

            // Free tree
            free_tree(root);
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

bool search(leaf *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number);
    }
    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    else if (number == tree->number)
    {
        return true;
    }
    return 1;
}