// Generic insertion sort.
// Big-O is O(n^2)
// Omega(n)
#include <stdio.h>

void insertion_sort(int n, int *data)
{
    for (int i = 1; i < n; ++i)
    {
        //looks at [0, key, 0, 0, 0]
        int key = data[i];
        //looks at [j, key, 0, 0, 0]
        int j = i - 1;
        while ((j >= 0) && (data[j] > key))
        {
            data[j + 1] = data[j];
            j = j - 1;
        }
        data[j + 1] = key;
    }
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

    insertion_sort(n, data);
    print(n, data);
}