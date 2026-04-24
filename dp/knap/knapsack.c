#include <stdlib.h>
#include <stdio.h>


#define MAX_ITEMS 105
#define MAX_WEIGHT 1005

// we initalize 2 arrays with max items of 105 to be safe
int value[MAX_ITEMS];
int weight[MAX_ITEMS];

// we initialize this 2D array with max items and max weight
int dp[MAX_ITEMS][MAX_WEIGHT];

int capacity;
int numitems;


// simple max function that chooses the largest of two integers
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

// for file input and for dp portion
int main(int argc, char *argv[]) {
    FILE *fp;
    
    fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &numitems);

    fscanf(fp, "%d", &capacity);

    // dp[0,0] will have value 0.
    value[0] = 0;
    weight[0] = 0;

    // we utilize 1-based indexing
    // take in the weight and then the value
    for (int i = 1; i <= numitems; i++) {
        int tempVal;
        int tempWeight;

        fscanf(fp, "%d %d", &tempWeight, &tempVal);
        value[i] = tempVal;
        weight[i] = tempWeight;
    }

    // initalize the dp 2D array with all 0's
    for (int i = 0; i <= numitems; i++) {
        for (int j = 0; j <= capacity; j++) {
            dp[i][j] = 0;
        }
    }

    // this part is when we choose what to take for our knapsack
    for (int i = 1; i <= numitems; i++) {
        for (int j = 1; j <= capacity; j++) {
            if (j >= weight[i]) {
                dp[i][j] = max(value[i] + dp[i-1][j-weight[i]], dp[i-1][j]);
            }
            else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    // total value will be the right bottom most element in our 2D array
    printf("Total value: %d\n", dp[numitems][capacity]);


    // to backtrack and find out what items we used
    // if the item above is different we took it, otherwise we skippped
    int currentWeight = capacity;
    for (int i = numitems; i > 0; i--) {
        if (dp[i][currentWeight] != dp[i-1][currentWeight]) {
            printf("Item %d\n", i);
            currentWeight = currentWeight - weight[i];
        }
    }

}