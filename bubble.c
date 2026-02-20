// Classic bubble sort.  Reads in data from an input file,
// sorts it, and prints the results
// Big-O(n^2) and Omega(n^2)
#include <stdio.h>

int bubble_sort(int n, int *data)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (data[i] > data[j])
            {
                int temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
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

    bubble_sort(n, data);
    print(n, data);
}