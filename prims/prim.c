#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct edge {
    int dest;
    int weight;
    struct edge *next;
} edge;

typedef struct {
    edge **adj;
    int num_vertices;
} graph;

typedef struct {
    int key;
    int value;
} heap_element;

typedef struct {
    int heap_size;
    int n;
    heap_element *data;
    int *index;
} heap;

#define LEFT(i) ((i<<1)+1)
#define RIGHT(i) ((i<<1)+2)
#define PARENT(i) ((i-1)>>1)

void heap_swap(heap *h, int i, int j) {
    heap_element h1 = h->data[i];
    h->data[i] = h->data[j];
    h->data[j] = h1;


    // swap the index between the two swapped heap_elements
    h->index[h->data[i].key] = i;
    h->index[h->data[j].key] = j;
}

void perc_up(heap *h, int i) {
    if (i == 0) {
        return;
    }

    if (h->data[i].value < h->data[PARENT(i)].value) {
        heap_swap(h, i, PARENT(i));
        perc_up(h, PARENT(i));
    }

}

void heap_insert(heap *h, int key, int value) {
    if (h->n >= h->heap_size) {
        return;
    }

    h->data[h->n].key = key;
    h->data[h->n].value = value;
    h->index[key] = h->n;
    ++h->n;

    perc_up(h, h->n-1);
}

void sift_down(heap *h, int i) {
    int smallest = i;

    if ((LEFT(i) < h->n) && (h->data[smallest].value > h->data[LEFT(i)].value)) {
        smallest = LEFT(i);
    }
    if ((RIGHT(i) < h->n) && (h->data[smallest].value > h->data[RIGHT(i)].value)) {
        smallest = RIGHT(i);
    }
    if (smallest != i) {
        heap_swap(h, smallest, i);
        sift_down(h, smallest);
    }
}

void heap_decrease_key(heap *h, int key, int new_value) {
    int i = h->index[key];
    h->data[i].value = new_value;
    perc_up(h, i);
}

int heap_extract(heap *h) {
    if (h->n == 0) {
        return -1;
    }

    int rv = h->data[0].key;
    h->data[0] = h->data[h->n-1];
    h->index[h->data[0].key] = 0;
    h->index[rv] = -1;
    --h->n;

    sift_down(h, 0);
    return rv;
}

int calc_mst(int *cost, int *previous, int n) {
    int total = 0;
    for (int i = 0; i < n; ++i) {
        if (previous[i] != -1) {
            total += cost[i];
        }
    }

    return total;
}

int prim(graph *g, int start) {
    int n = g->num_vertices;

    heap h;
    h.heap_size = n;
    h.n = 0;
    h.data = malloc(n * sizeof(heap_element));
    h.index = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        h.index[i] = -1;
    }

    int *cost = malloc(n * sizeof(int)); // for the cheapest cost for each vertex
    int *previous = malloc(n * sizeof(int)); // the prev cheapest vertex connected
    int *in_tree = malloc(n * sizeof(int)); // all the vertexes in the in_tree, set to 0 if in tree, set to 1 if in tree


    // this is to initialize all the data in the heap
    for (int i = 0; i < n; ++i) {
        cost[i] = INT_MAX; // set each cost to infinity which would be the largest size of int
        previous[i] = -1; // we want the previous array to be -1 for all to show that none of them have predecessors yet
        in_tree[i] = 0; // // we want to se the in_tree array elements to signify none of them have been taken into account for
        heap_insert(&h, i, INT_MAX); // we then add each vertex in the heap with the default values
    }

    // we start with the first vertex and we update the heap with this too
    cost[start] = 0;
    heap_decrease_key(&h, start, 0);


    // we run a loop while there are elements in the heap
    while (h.n > 0) {
        int v = heap_extract(&h); // we take out the minimum element on top first
        in_tree[v] = 1;

        edge *e1 = g->adj[v];
        while (e1 != NULL) {
            int z = e1->dest;
            int w = e1->weight;

            if ((in_tree[z] == 0) && w < cost[z]) {
                cost[z] = w;
                previous[z] = v;
                heap_decrease_key(&h, z, w);
            }
            
            e1 = e1->next;
        }
    }

    return calc_mst(cost, previous, n);
}




int main(int argc, char *argv[]) {
    FILE *fp;
    int num_v;
    int num_e;

    // gets the # of vertices
    fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &num_v);

    // gets the # of edges
    fscanf(fp, "%d", &num_e);

    graph g;
    g.num_vertices = num_v;
    g.adj = malloc(num_v*sizeof(edge *));

    // initalizes each edge in the adj list to NULL
    for (int i = 0; i < num_v; ++i) {
        g.adj[i] = NULL;
    }

    // looks at each edge and creates two (one for each vertex)
    for (int i = 0; i < num_e; ++i) {
        int u;
        int v;
        int w;
        
        fscanf(fp, "%d", &u);
        fscanf(fp, "%d", &v);
        fscanf(fp, "%d", &w);

        edge *e1 = malloc(sizeof(edge));
        e1->dest = v;
        e1->weight = w;
        e1->next = g.adj[u];
        g.adj[u] = e1;

        edge *e2 = malloc(sizeof(edge));
        e2->dest = u;
        e2->weight = w;
        e2->next = g.adj[v];
        g.adj[v] = e2;
    }

    

    int mst = prim(&g, 0);
    printf("%d\n", mst);
    return 0;
}