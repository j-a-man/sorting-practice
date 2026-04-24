#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct for the table
typedef struct
{
    int prior;
    int count;
} entry;

//initialize table and sublength so trace func can access
entry table[101][101];
int sublength = 0;

void trace(char *string1, char *string2, int rows, int columns) {
    //recursive base case
    if (table[rows][columns].prior == -1 || rows <= 0 || columns <= 0) {
        return;
    }
    
    //traverse back up to find the LCS
    if (table[rows][columns].prior == 0) {
        trace(string1, string2, rows, columns - 1);
    }
    else if (table[rows][columns].prior == 1) {
        trace(string1, string2, rows - 1, columns);
    } 
    else if (table[rows][columns].prior == 2) {
        trace(string1, string2, rows - 1, columns - 1);
        sublength++;
        printf("%c", string1[columns-1]);
    }
}



int main() {
    
    
    char *string1;
    char *string2;

    //take input in via scanf
    scanf("%s", &string1[0]);
    scanf("%s", &string2[0]);

    int len1 = strlen(&string1[0]);
    int len2 = strlen(&string2[0]);

    //initalize the table
    for (int r = 0; r <= len2; ++r) {
        table[r][0].count = 0;
        table[r][0].prior = -1;
    }
    for (int c = 0; c <= len1; ++c) {
        table[0][c].count = 0;
        table[0][c].prior = -1;
    }

    //start putting in correct values in table
    for (int r = 1; r <= len2; ++r) {
        for (int c = 1; c <= len1; ++c) {
            table[r][c].count = 0;

            if (string1[c-1] == string2[r-1]) {
                table[r][c].count = table[r-1][c-1].count+1;
                table[r][c].prior = 2;
            }
            else {
                if (table[r][c-1].count >= table[r-1][c].count) {
                    table[r][c].count = table[r][c-1].count;
                    table[r][c].prior = 0;
                }

                else {
                    table[r][c].count = table[r-1][c].count;
                    table[r][c].prior = 1;
                }
            }
        }
    }

    //print for formatting
    printf("LCS: ");
    trace(string1, string2, len2, len1);
    printf("\nLength: %d\n", sublength);
    return 0;


}