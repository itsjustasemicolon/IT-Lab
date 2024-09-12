#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node *insertNode(struct Node *root, int data)
{
    if (root == NULL)
    {
        root = createNode(data);
        return root;
    }

    char direction;
    printf("Insert left (l) or right (r) of %d? ", root->data);
    scanf(" %c", &direction);

    if (direction == 'l')
    {
        root->left = insertNode(root->left, data);
    }
    else if (direction == 'r')
    {
        root->right = insertNode(root->right, data);
    }
    else
    {
        printf("Invalid choice\n");
    }

    return root;
}

void inOrder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void preOrder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
}

int main()
{
    struct Node *root = NULL;
    int choice, data;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Create/Insert a node\n");
        printf("2. In-order Traversal\n");
        printf("3. Pre-order Traversal\n");
        printf("4. Post-order Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the data to insert: ");
            scanf("%d", &data);
            root = insertNode(root, data);
            break;
        case 2:
            printf("In-order traversal: ");
            inOrder(root);
            printf("\n");
            break;
        case 3:
            printf("Pre-order traversal: ");
            preOrder(root);
            printf("\n");
            break;
        case 4:
            printf("Post-order traversal: ");
            postOrder(root);
            printf("\n");
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
