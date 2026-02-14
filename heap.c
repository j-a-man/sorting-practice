//CS 375 2/5/26
//Jaylin Man
//Heapsort

#include <stdio.h>
#include <stdlib.h>


#define PARENT(i) ((i-1) >> 1)
#define LEFT(i) ((i<<1) + 1)
#define RIGHT(i) ((i<<1) + 2)

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *heap, int heap_size, int i) {
    int largest = i;
    if ((LEFT(i) < heap_size) && (heap[largest] < heap[LEFT(i)])) {
        largest = LEFT(i);
    }
    if ((RIGHT(i) < heap_size) && (heap[largest] < heap[RIGHT(i)])) {
        largest = RIGHT(i);
    }
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(heap, heap_size, largest);
    }

}

void build_max_heap(int *heap, int n) {
    for (int i = n/2; i >= 0; --i) {
        heapify(heap, n, i);
    }
}

void heap_sort(int *heap, int n) {
    build_max_heap(heap, n);
    for (int i = n-1; i > 0; --i) {
        swap(&heap[0], &heap[i]);
        n-=1;
        heapify(heap, n, 0);
    }
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

    heap_sort(data, n);
    print(n, data);

    return 0;
}