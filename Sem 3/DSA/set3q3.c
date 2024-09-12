#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    }

    char direction;
    printf("Insert left (l) or right (r) of %d? ", root->data);
    scanf(" %c", &direction);

    if (direction == 'l') {
        root->left = insert(root->left, data);
    } else if (direction == 'r') {
        root->right = insert(root->right, data);
    } else {
        printf("Invalid choice\n");
    }

    return root;
}

struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

void inOrder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

struct Node* findMin(struct Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct Node* findMax(struct Node* root) {
    while (root && root->right != NULL) {
        root = root->right;
    }
    return root;
}

void findPredecessorSuccessor(struct Node* root, int key, struct Node** predecessor, struct Node** successor) {
    if (root == NULL) {
        return;
    }

    if (root->data == key) {
        if (root->left != NULL) {
            *predecessor = findMax(root->left);
        }

        if (root->right != NULL) {
            *successor = findMin(root->right);
        }
        return;
    }

    if (key < root->data) {
        *successor = root;  
        findPredecessorSuccessor(root->left, key, predecessor, successor);
    } else {
        *predecessor = root;  
        findPredecessorSuccessor(root->right, key, predecessor, successor);
    }
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main() {
    struct Node* root = NULL;
    int choice, key;
    struct Node *predecessor, *successor;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create/Insert a node\n");
        printf("2. Search for a key\n");
        printf("3. Find In-order Predecessor and Successor of a key\n");
        printf("4. Delete a key\n");
        printf("5. In-order Traversal\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Key inserted successfully!\n");
                break;

            case 2:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                if (search(root, key)) {
                    printf("Key %d found in the tree.\n", key);
                } else {
                    printf("Key %d not found in the tree.\n", key);
                }
                break;

            case 3:
                printf("Enter the key to find predecessor and successor: ");
                scanf("%d", &key);
                predecessor = NULL;
                successor = NULL;
                findPredecessorSuccessor(root, key, &predecessor, &successor);
                if (predecessor) {
                    printf("Predecessor of %d is %d\n", key, predecessor->data);
                } else {
                    printf("No Predecessor of %d\n", key);
                }
                if (successor) {
                    printf("Successor of %d is %d\n", key, successor->data);
                } else {
                    printf("No Successor of %d\n", key);
                }
                break;

            case 4:
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                printf("Key %d deleted from the tree.\n", key);
                break;

            case 5:
                printf("In-order traversal of the tree: ");
                inOrder(root);
                printf("\n");
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
