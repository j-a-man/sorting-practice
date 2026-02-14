#include <stdio.h>

int binary_search(int n, int *data, int target) {
  int left = 0;
  int right = n - 1;
  int mid = (left + right) / 2;

  // makes sure that left and right don't overlap
  while (left <= right) {
    // if mid is data[target], then we return that index
    if (target == data[mid]) {
      return mid;
      // we increase left side
    } else if (target > data[mid]) {
      left = mid + 1;
      // we increase right side
    } else if (target < data[mid]) {
      right = mid - 1;
    }
    // update mid pointer based on new right and left
    mid = (left + right) / 2;
  }
  // return -1 when the target isn't fonud
  return -1;
}

int main(int argc, char *argv[]) {
  FILE *fp;
  int n;

  // reads first num to see how long data will be
  fp = fopen(argv[1], "r");
  fscanf(fp, "%d", &n);
  // scans the input to put into data array
  int data[n];
  for (int i = 0; i < n; ++i)
    fscanf(fp, "%d", &data[i]);

  // reads first num to see how long inputs of target will be
  int m;
  fscanf(fp, "%d", &m);
  int input[m];
  // scans the rest to put into an array inputs which will later call binary
  // search
  for (int i = 0; i < m; ++i) {
    fscanf(fp, "%d", &input[i]);
  }

  // loop to call binary search based on the number of target inputs
  int output;
  for (int i = 0; i < m; ++i) {
    output = binary_search(n, data, input[i]);
    // if output is -1, that means the target wasn't found
    if (output == -1) {
      printf("Not found\n");
      // if output is anything else besides -1, then that is the index we print
    } else {
      printf("%d\n", output);
    }
  }

  // important to close fp
  fclose(fp);
  return 0;
}