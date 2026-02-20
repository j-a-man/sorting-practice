// Using the built-in quicksort
#include <stdio.h>
#include <stdlib.h>


int compare(int *a, int *b)
{
    if (*a > *b) return 1;
    if (*a < *b) return -1;

    return 0;
}

void print(int n, int *data)
{
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%d\n", data[i]);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int n;

    fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &n);

    int data[n];
    for (int i = 0; i < n; ++i)
        fscanf(fp, "%d", &data[i]);

    qsort(data, n, sizeof(int), compare);
    print(n, data);
}