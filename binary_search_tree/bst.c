#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node *right ;
    struct Node *left;
} Node;

void print(int *data, int *delData, int n_i, int n_d) {
    printf("Elements to insert: %d\n", n_i);
    for (int i = 0; i < n_i; ++i) {
        printf("%d\n", data[i]);
    }


    printf("Elements to delete: %d\n", n_d);
    for (int i = 0; i < n_d; ++i) {
        printf("%d\n", delData[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int n_i;
    int n_d;

    fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &n_i);

    int data[n_i];
    for (int i = 0; i < n_i; ++i) {
        fscanf(fp, "%d", &data[i]);
    }

    int delData[n_d];
    fscanf(fp, "%d", &n_d);
    for (int i = 0; i < n_d; ++i) {
        fscanf(fp, "%d", &delData[i]);
    }

    print(data, delData, n_i, n_d);
}