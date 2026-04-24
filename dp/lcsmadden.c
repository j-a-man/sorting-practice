#include <stdio.h>
#include <string.h>

#define HORIZ 0
#define VERT 1
#define DIAG 2
#define INVALID -1

typedef struct
{
  int count;
  int prior;
} entry;

#define MAXLEN 100

entry table[MAXLEN][MAXLEN];
char s1[MAXLEN];
char s2[MAXLEN];

void trace(int row, int column)
{
  switch (table[row][column].prior)
  {
  case HORIZ:
    trace(row, column - 1);
    break;
  case VERT:
    trace(row - 1, column);
    break;
  case DIAG:
    trace(row - 1, column - 1);
    printf("%c", s1[column]);
    break;
  }
}

char translate(int v)
{
  switch (v)
  {
  case HORIZ:
    return '<';
    break;
  case VERT:
    return '^';
    break;
  case DIAG:
    return '\\';
    break;
  default:
    return ' ';
  }

  return ' ';
}

int main()
{

  scanf("%s", &s1[1]);
  scanf("%s", &s2[1]);

  int len1 = strlen(&s1[1]);
  int len2 = strlen(&s2[1]);

  for (int r = 0; r <= len2; ++r)
  {
    table[r][0].count = 0;
    table[r][0].prior = INVALID;
  }
  for (int c = 0; c <= len1; ++c)
  {
    table[0][c].count = 0;
    table[0][c].prior = INVALID;
  }

  // Now fill the table
  for (int r = 1; r <= len2; ++r)
    for (int c = 1; c <= len1; ++c)
    {
      table[r][c].count = 0;

      // Match
      if (s1[c] == s2[r])
      {
        table[r][c].count = table[r - 1][c - 1].count + 1;
        table[r][c].prior = DIAG;
      }

      if (table[r][c - 1].count > table[r][c].count)
      {
        table[r][c].count = table[r][c - 1].count;
        table[r][c].prior = HORIZ;
      }

      if (table[r - 1][c].count > table[r][c].count)
      {
        table[r][c].count = table[r - 1][c].count;
        table[r][c].prior = VERT;
      }
    }

  printf("LCS: ");
  trace(len2, len1);
  printf("\n");
  printf("Length: %d\n", table[len2][len1].count);

  printf("         ");
  for (int c = 1; c <= len1; ++c)
    printf("   %c   ", s1[c]);
  printf("\n");

  for (int r = 0; r <= len2; ++r)
  {
    if (r > 0)
      printf("%c ", s2[r]);
    else
      printf("  ");
    for (int c = 0; c <= len1; ++c)
      printf("[%2d %c] ", table[r][c].count, translate(table[r][c].prior));
    printf("\n");
  }
}
