/// Selection sort.
// Big-O(n^2) and Omega(n^2)
#include <stdio.h>

void selection_sort(int n, int *data) {
  for (int i = 0; i < n; ++i) {
    int smallest = i;
    for (int j = i + 1; j < n; ++j) {
      if (data[j] < data[smallest])
        smallest = j;
    }
    // Swap the smallest elemeent into spot i
    int temp = data[i];
    data[i] = data[smallest];
    data[smallest] = temp;
  }
}

void print(int n, int *data) {
  printf("%d\n", n);
  for (int i = 0; i < n; ++i)
    printf("%d\n", data[i]);
}

int main(int argc, char *argv[]) {
  FILE *fp;
  int n;

  fp = fopen(argv[1], "r");
  fscanf(fp, "%d", &n);

  int data[n];
  for (int i = 0; i < n; ++i)
    fscanf(fp, "%d", &data[i]);

  selection_sort(n, data);
  print(n, data);
}