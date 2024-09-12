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

int search(int inOrder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inOrder[i] == value) {
            return i;
        }
    }
    return -1;
}

struct Node* buildTree(int inOrder[], int preOrder[], int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd) {
        return NULL;
    }

    struct Node* root = createNode(preOrder[*preIndex]);
    (*preIndex)++;

    if (inStart == inEnd) {
        return root;
    }

    int inIndex = search(inOrder, inStart, inEnd, root->data);

    root->left = buildTree(inOrder, preOrder, inStart, inIndex - 1, preIndex);
    root->right = buildTree(inOrder, preOrder, inIndex + 1, inEnd, preIndex);

    return root;
}

void inOrderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

void preOrderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void postOrderTraversal(struct Node* root) {
    if (root == NULL) {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
}

int main() {
    int n;
    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &n);

    int inOrder[n], preOrder[n];
    
    printf("Enter the in-order traversal:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &inOrder[i]);
    }

    printf("Enter the pre-order traversal:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &preOrder[i]);
    }

    int preIndex = 0;

    struct Node* root = buildTree(inOrder, preOrder, 0, n - 1, &preIndex);

    printf("In-order traversal of the constructed tree: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Pre-order traversal of the constructed tree: ");
    preOrderTraversal(root);
    printf("\n");
    
    printf("Post-order traversal of the constructed tree: ");
    postOrderTraversal(root);
    printf("\n");

    return 0;
}
