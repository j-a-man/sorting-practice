// Simple Huffman encoding program
#include <stdio.h>

// Huffman builds a tree for the encoding.  As the
// tree is constructed, each node will have left and right
// index (to either letters at the bottom, or internal tree
// nodes).
//
// The final letters will each have a series of bits for
// the encoding.
//
// For internal nodes of the tree, left and right will
// be indexes.  For the "bottom level" leaves, left and
// right values are -1
typedef struct
{
  char letter;
  int frequency;
  int left, right;
  int numbits;
  int bits[100];
} treenode;
// The encoding tree
int treesize;
treenode tree[100];

// Heap to maintain the letters that need to be
// merged
int heapsize;
int heap[100];

// Heap code
int parent(int i)
{
  return (i - 1) / 2;
}

int left(int i)
{
  return i * 2 + 1;
}
int right(int i)
{
  return i * 2 + 2;
}

// For comparisons in the heap.  To ensure
// cosistency in how the tree is built, we use
// the actual letter for tie-breaking, in the
// case that the frequencies are identical.
//
// Without this, different sorts of trees might
// get built.
//
// Uses the global tree array (i and j index into this;
// kind of a hack, trying to keep the code short and simple).
int less(int i, int j)
{
#if 0
  printf("Compare %d [%c %d]   %d [%c %d]\n",
	 heap[i], tree[heap[i]].letter, tree[heap[i]].frequency,
	 heap[j], tree[heap[j]].letter, tree[heap[j]].frequency);
#endif

  if (tree[heap[i]].frequency < tree[heap[j]].frequency)
    return 1;
  if (tree[heap[i]].frequency > tree[heap[j]].frequency)
    return -1;

  if (tree[heap[i]].letter < tree[heap[j]].letter)
    return 1;
  if (tree[heap[i]].letter > tree[heap[j]].letter)
    return -1;

  return 0;
}

void heapify(int i)
{
  int l, r, smallest;

  l = left(i);
  r = right(i);

  smallest = i;
  if (l < heapsize && (less(l, i) == 1))
    smallest = l;
  if (r < heapsize && (less(r, smallest) == 1))
    smallest = r;

  if (smallest != i)
  {
    int tmp = heap[i];
    heap[i] = heap[smallest];
    heap[smallest] = tmp;

    heapify(smallest);
  }
}

void heap_insert(int value)
{
  int i = heapsize;
  heap[heapsize++] = value;

  // printf("Insert %d at %d\n", value, i);

  while ((i > 0) && (less(parent(i), i) == -1))
  {
    // printf("Swap up");

    int tmp = heap[parent(i)];
    heap[parent(i)] = heap[i];
    heap[i] = tmp;
    i = parent(i);
  }
}

// Gets the top element of the heap
int heap_pop()
{
  int rv = heap[0];
  heap[0] = heap[heapsize - 1];
  --heapsize;
  heapify(0);

  return rv;
}

// Handy for debugging
void show_heap()
{
  int i;
  for (i = 0; i < heapsize; ++i)
    printf("Heap %d->%d: %c %d\n", i, heap[i],
           tree[heap[i]].letter,
           tree[heap[i]].frequency);
}

void show_encoding(int i, int *encoding, int numbits)
{
  printf("Tree element %d, left %d right %d freq %d letter %c\n",
         i, tree[i].left, tree[i].right, tree[i].frequency, tree[i].letter);

  if (tree[i].left == -1)
  {
    int j;
    // We're done
    tree[i].numbits = numbits;
    printf("%c: ", tree[i].letter);
    for (j = 0; j < numbits; ++j)
    {
      printf(" %d", encoding[j]);
      tree[i].bits[j] = encoding[j];
    }
    printf("\n");
  }
  else
  {
    encoding[numbits] = 0;
    show_encoding(tree[i].left, encoding, numbits + 1);
    encoding[numbits] = 1;
    show_encoding(tree[i].right, encoding, numbits + 1);
  }
}

// Used to find the appropriate bits for any given message letter
int find_letter(char letter)
{
  int i;

  for (i = 0; i < treesize; ++i)
  {
    if (tree[i].letter == letter)
      return i;
  }

  printf("Could not find letter!\n");
  return 0;
}

// Prints out the bits for a letter
void show_letter(char letter)
{
  int i;

  for (i = 0; i < treesize; ++i)
  {
    if (tree[i].letter == letter)
    {
      int j;

      for (j = 0; j < tree[i].numbits; ++j)
        printf("%d ", tree[i].bits[j]);
    }
  }
}

// The program reads in the number of letters to
// handle, and the frequencies of each of these letters.
//
// After that, we build the Huffman tree.
int main(int argc, char *argv[])
{
  int numletters, numdigits;
  int i;
  int encoding[100];

  heapsize = 0;

  scanf("%d", &numletters);
  for (i = 0; i < numletters; ++i)
  {
    scanf(" %c %d", &tree[i].letter, &tree[i].frequency);
    tree[i].left = tree[i].right = -1;
    heap_insert(i);
  }
  treesize = i;

  show_heap();

  while (heapsize > 1)
  {
    int l = heap_pop();
    int r = heap_pop();
    printf("Pop %d %c %d  and %d %c %d\n",
           l, tree[l].letter, tree[l].frequency,
           r, tree[r].letter, tree[r].frequency);
    show_heap();

    tree[treesize].left = l;
    tree[treesize].right = r;
    if (tree[l].letter < tree[r].letter)
      tree[treesize].letter = tree[l].letter;
    else
      tree[treesize].letter = tree[r].letter;
    tree[treesize].frequency = tree[l].frequency + tree[r].frequency;
    heap_insert(treesize);
    ++treesize;
  }

  printf("Encode from %d\n", treesize - 1);

  show_encoding(treesize - 1, encoding, 0);

  // Now we will read in the message, and convert each
  // letter into a series of bits.
  char mssg[100];
  scanf("%s", mssg);

  int totbits = 0;
  for (i = 0; mssg[i] != '\0'; ++i)
  {
    int j;

    j = find_letter(mssg[i]);
    totbits += tree[j].numbits;
  }

  printf("%d\n", totbits);

  for (i = 0; mssg[i] != '\0'; ++i)
    show_letter(mssg[i]);

  printf("\n");
}
