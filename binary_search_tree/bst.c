#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *right;
    struct Node *left;
} Node;

Node *createNewNode(int val) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->value = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Node *treeMinimum(Node *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}


Node *insertNode(Node *root, int val) {
    if (root == NULL) {
        return createNewNode(val);
    }
    else if (val < root->value) {
        root->left = insertNode(root->left, val);
    }
    else if (val > root->value) {
        root->right = insertNode(root->right, val);
    }
    return root;
}

Node* deleteNode(Node *root, int val) {
    if (root == NULL) {
        return root;
    }

    if (val < root->value) {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->value) {
        root->right = deleteNode(root->right, val);
    }
    else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = treeMinimum(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}

void inOrder(Node *root, int count) {
    if (root != NULL) {
        inOrder(root->left, count+1);
        printf("%d: %d\n", root->value, count);
        inOrder(root->right, count+1);
    }
}


int main(int argc, char *argv[]) {
    FILE *fp;
    int n_i;
    int n_d;
    int temp;
    Node *root = NULL;

    fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &n_i);

    fscanf(fp, "%d", &temp);
    root = insertNode(root, temp);

    for (int i = 1; i < n_i; ++i) {
        fscanf(fp, "%d", &temp);
        root = insertNode(root, temp);
    }

    fscanf(fp, "%d", &n_d);
    for (int i = 0; i < n_d; ++i) {
        fscanf(fp, "%d", &temp);
        root = deleteNode(root, temp);
    }

    inOrder(root, 0);
}