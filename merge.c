//CS 375 2/5/26
//Jaylin Man
//Mergesort

#include <stdio.h>
#include <stdlib.h>

void merge(int *A, int p, int q, int r) {
    int i, j, k;
    
    printf("P: %d\nQ: %d\nR: %d\n",p,q,r);

    int nL = q-p+1;
    int nR = r-q;

    int L[nL];
    int R[nR];

    for (i = 0; i < nL; i++) {
        L[i] = A[p+i];
    }
    for (j = 0; j < nR; j++) {
        R[j] = A[q+1+j];
    }


    //int z = 0;
    //printf("This is the left side array: \n");
    //for (z = 0; z < nL; ++z) {
    //    printf("%d\n", L[i]);
    //}
    //printf("Right side array: \n");
    //for (z = 0; z < nR; ++z) {
    //    printf("%d\n", R[i]);
    //}
    //printf("\n");




    i = 0;
    j = 0;
    k = p;

    while ((i < nL) && (j < nR)) {
        if (L[i] <= R[i]) {
            A[k] = L[i];
            i+=1;
        }
        else {
            A[k] = R[j];
            j+=1;
        }
        k++;
    }


    while (i < nL) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < nR) {
        A[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int *A, int p, int r) {
    if (p >= r) {
        return;
    }
    
    
    //for (int i = 0; i < r; ++i) {
    //    printf("%d\n", A[i]);
    //}
    //printf("break\n");
    

    int q = (p+r)/2;
    merge_sort(A, p, q);
    merge_sort(A, q+1, r);

    merge(A, p, q, r);
}

void print(int n, int *data) {
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", data[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int n;

    fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &n);

    int data[n];
    for (int i = 0; i < n; ++i) {
        fscanf(fp, "%d", &data[i]);
    }

    merge_sort(data, 0, n-1);

    printf("\nOutput: \n");
    print(n, data);

    return 0;
}