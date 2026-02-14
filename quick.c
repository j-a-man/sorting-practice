//CS 375 2/4/26
//Jaylin Man
//Quicksort with Hoare Partition

#include <stdio.h>
#include <stdlib.h>

//swaps the value between the two points
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int hoare_partition(int *data, int m, int n) {
    //uses two pointers and meets in the middle for the pivot
    int r = m;

    //uses randomization to find the pivot point
    //has case where m-n+1 can't be 0 so no floating point exception occurs
    if ((m-n+1) != 0) {
        r = m + ((random())%(m-n+1));
    }


    int x = data[r];
    //sets the two pointers to outside the array bounds
    int i = m-1;
    int j = n+1;
    int temp;


    while (1) {
        //right pointer moves towards the left side while value is greater than pivot point
        do {
            j = j - 1;
        } while (data[j] > x);

        //left pointer moves towards the right side as value is less than pivot point
        do {
            i = i + 1;
        } while (data[i] < x);

        //keep going and swapping until i is less than j
        if (i < j) {
            swap(&data[i], &data[j]);
        }
        //this would be the partition point
        else { 
            return j;
        }
    }

}

void quick_sort(int *data, int m, int n) {
    if (m < n) {
        int par = hoare_partition(data, m, n);  //finds the pivot point
        quick_sort(data, m, (par-1));   //recursively sorts left side
        quick_sort(data, (par + 1), n); //recursively sorts right side
    }
}

//print function to print out the array sorted and the size
void print(int n, int *data)
{
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%d\n", data[i]);
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int n;

    fp = fopen(argv[1], "r");
    fscanf(fp,"%d", &n);

    int data[n];
    for (int i = 0; i < n; ++i) {
        fscanf(fp, "%d", &data[i]);
    }
    //calls quicksort
    quick_sort(data, 0, n);

    //prints out the sorted array with the print function
    print(n, data);

    return 0;
}