// Simple program to generate a file with random
// numbers (the first line will be the total number
// of numbers).
//
// % make make_data
// % ./make_data 10 > data10.txt
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);

    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
    {
        printf("%d\n", (int)(random() % 100000));
    }
}