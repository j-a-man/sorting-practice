#include <stdio.h>
#include <stdlib.h>

// Prim’s Algorithm:
// Start with a heap of vertices (each with infinite distance)
// Pick a start vertex, set the distance to zero
// In a loop…
//  Pull a vertex out of the heap
//  Mark the vertex as being part of the tree
//  For every edge leaving the vertex (to a vertex not already in the tree)
//  If the length of the edge is less than the current distance, update
// Stop when every vertex is part of the growing tree

#define PARENT(i) ((i - 1) >> 1)
#define LEFT(i) ((i << 1) + 1)
#define RIGHT(i) ((i << 1) + 2)

#define INF 1000000000

typedef struct {
    int key;
    int value;
} heap_element;

typedef struct {
    int heap_size; // capacity
    int n; // num of elements
    heap_element *data; // pointer to heap element
    int *index;
} heap;

typedef struct edge {
    int to; // where edge points to
    int weight; // cost
    struct edge *next; // next edge
} edge;

typedef struct {
    edge **edges; // adjacency list
    int num_vertices;
} graph;

void heap_swap(heap *h, int i, int j) {
    heap_element temp = h->data[i];
    h->data[i] = h->data[j];
    h->data[j] = temp;
    // Fix indexes
    h->index[h->data[i].key] = i;
    h->index[h->data[j].key] = j;
}

void perc_up(heap *h, int i) {
    if (i == 0)
    return;
    if (h->data[i].value < h->data[PARENT(i)].value) {
        heap_swap(h, i, PARENT(i));
        perc_up(h, PARENT(i));
    }
}

void insert(heap *h, int key, int value) {
    h->data[h->n].key = key;
    h->data[h->n].value = value;
    h->index[key] = h->n;
    h->n++;
    perc_up(h, h->n - 1);
}



void sift_down(heap *h, int i) {
    int smallest = i;
    if ((LEFT(i) < h->n) && (h->data[LEFT(i)].value < h->data[smallest].value))
    smallest = LEFT(i);
    if ((RIGHT(i) < h->n) && (h->data[RIGHT(i)].value < h->data[smallest].value))
    smallest = RIGHT(i);
    if (smallest != i) {
        heap_swap(h, i, smallest);
        sift_down(h, smallest);
    }
}

void decrease_key(heap *h, int key, int new_value) {
    int i = h->index[key];
    h->data[i].value = new_value;
    perc_up(h, i);
}

int heap_extract(heap *h) {
    if (h->n == 0)
    return -1;
    int rv = h->data[0].key;
    h->n--;
    // Move last element to top and fix index
    h->data[0] = h->data[h->n];
    h->index[h->data[0].key] = 0;
    h->index[rv] = -1;
    
    sift_down(h, 0);
    return rv;
}

// Prims Algorithm

int prim(edge **G, int v) {
    int *cost = malloc(v * sizeof(int));
    int *previous = malloc(v * sizeof(int));
    int *in_tree = malloc(v * sizeof(int));

    // Start with a heap of vertices each with inf distance
    heap h;
    h.n = 0;
    h.heap_size = v;
    h.data = malloc(v * sizeof(heap_element));
    h.index = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        cost[i] = INF;
        previous[i] = -1;
        in_tree[i] = 0;
        insert(&h, i, INF);
    }

    // start vertex 0 set distance to zero
    cost[0] = 0;
    decrease_key(&h, 0, 0);

    while (h.n > 0) {
        // pull a vertex out of heap
        int u = heap_extract(&h);
        in_tree[u] = 1;

        // for every edge leaving u
        edge *e = G[u];
        while (e != NULL) {
            int z = e->to;
            if (!in_tree[z] && e->weight < cost[z]) {
                // if the length of the edge is less than current distance update
                cost[z] = e->weight;
                previous[z] = u;
                decrease_key(&h, z, e->weight);
            }
            e = e->next;
        }
    }

    int total = 0;
    for (int i = 1; i < v; i++) {
        if (previous[i] != -1) {
            total += cost[i];
        }
    }
    printf("%d\n", total);
    return total;
}


int main(int argc, char *argv[]) {
    FILE *fp;
    int v; // vertices
    int e; // edges

    fp = fopen(argv[1], "r");
    fscanf(fp, "%d %d", &v, &e);

    // build adjacency list
    edge **G = malloc(v * sizeof(edge *));
    for (int i = 0; i < v; i++)
        G[i] = NULL;

    for (int i = 0; i < e; i++) {
        int u, w, weight;
        fscanf(fp, "%d %d %d", &u, &w, &weight);

        // add edge u to w
        edge *eu = malloc(sizeof(edge));
        eu->to = w;
        eu->weight = weight;
        eu->next = G[u];
        G[u] = eu;

        // add edge w to u
        edge *ew = malloc(sizeof(edge));
        ew->to = u;
        ew->weight = weight;
        ew->next = G[w];
        G[w] = ew;
    }

    prim(G, v);
    return 0;
}