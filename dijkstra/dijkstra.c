#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

//represents an individual edge in the graph
typedef struct edge {
    int dest;
    int weight;
    struct edge *next;
} edge;

//the overall structure of the graph representation
typedef struct {
    edge **adj;
    int *parent;
    int *dist;
    int num_vertices;
} graph;

//represents an individual element in the heap
typedef struct {
    int key;
    int value;
} heap_element;

//the overall structure of the heap
typedef struct {
    int capacity;
    int size;
    heap_element *data;
    int *index;
} heap;

//easy access to find parent, left, right in heap
#define LEFT(i) ((i<<1)+1)
#define RIGHT(i) ((i<<1)+2)
#define PARENT(i) ((i-1)>>1)

//swaps two different heap elements
void heap_swap(heap *h, int i, int j) {
    heap_element h1 = h->data[i];
    h->data[i] = h->data[j];
    h->data[j] = h1;

    h->index[h->data[i].key] = i;
    h->index[h->data[j].key] = j;
}

//initializes the heap
heap *createHeap(int capacity) {
    heap *h = malloc(sizeof(heap));
    h->size = 0;
    h->capacity = capacity;
    h->data = malloc(capacity*sizeof(heap_element));
    h->index = malloc(capacity*sizeof(int));
    for (int i = 0; i < capacity; ++i) {
        h->index[i] = -1;
    }
    return h;
}

//initializes a new element in the heap
heap_element *newHeapElement(int i, int dist) {
    heap_element *e3 = malloc(sizeof(heap_element));
    e3->key = i;
    e3->value = dist;
    return e3;
}

// swaps elements to maintain the min-heap property
void perc_up(heap *h, int i) {
    if (i == 0) {
        return;
    }

    if (h->data[i].value < h->data[PARENT(i)].value) {
        heap_swap(h, i, PARENT(i));
        perc_up(h, PARENT(i));
    }
}

//reduces value of specific node and restores heap's properties
void heap_decrease_key(heap *h, int key, int new_value) {
    int i = h->index[key];
    h->data[i].value = new_value;
    perc_up(h,i);
}


//inserts an element in the heap and calls perc_up to adjust where needed
void heap_insert(heap *h, int vertex, int dist) {
    if (h->size >= h->capacity) {
        return;
    }
    h->data[h->size].value = dist;
    h->data[h->size].key = vertex;
    h->index[vertex] = h->size;
    h->size++;

    perc_up(h,h->size-1);
}

//moves an element down appropriately in heap
void perc_down(heap *h, int i) {
    int smallest = i;

    if ((LEFT(i) < h->size) && (h->data[smallest].value > h->data[LEFT(i)].value)) {
        smallest = LEFT(i);
    }
    if ((RIGHT(i) < h->size) && (h->data[smallest].value > h->data[RIGHT(i)].value)) {
        smallest = RIGHT(i);
    }
    if (smallest != i) {
        heap_swap(h, smallest, i);
        perc_down(h, smallest);
    }
}

//takes out the top element in the heap
int heap_extract_min(heap *h) {
    if (h->size == 0) {
        return -1;
    }

    int rv = h->data[0].key;
    h->data[0] = h->data[h->size-1];
    h->index[h->data[0].key] = 0;
    h->index[rv] = -1;
    h->size--;

    perc_down(h,0);
    return rv;
}

//starts from the top most parent and prints downwards
void printPath(int *parent, int j) {
    if (parent[j] == -1) {
        printf("%d ", j);
        return;
    }

    printPath(parent, parent[j]);
    printf("%d ", j);
}

void dijkstra(graph *g, int start, int end) {
    int n = g->num_vertices;
    heap *h = createHeap(n);

    //set to infinity
    for (int i = 0; i < n; ++i) {
        g->dist[i] = 999999;
        g->parent[i] = -1;
        heap_insert(h, i, 999999);
    }

    g->dist[start] = 0;
    heap_decrease_key(h, start, 0); // update heap to reflect changes

    while (h->size > 0) { // run until heap is empty
        int u = heap_extract_min(h);
        if (g->dist[u] == 999999) {
            break;
        }
        edge *curr = g->adj[u];
        while (curr != NULL) {
            int v = curr->dest;
            int weight = curr->weight;

            if (h->index[v] != -1 && g->dist[u] + weight < g->dist[v]) { // updates distance if shorter path is found
                g->dist[v] = g->dist[u] + weight;
                g->parent[v] = u;
                heap_decrease_key(h, v, g->dist[v]);
            }
            curr = curr->next;
        }
    }

    if (g->dist[end] >= 999999) {
        printf("not connected\n"); // checks to see if graph is connected
    }
    else {
        printf("Distance:  %d\n", g->dist[end]);
        printf("Path:\t");
        printPath(g->parent, end);
        printf("\n");
    }


}


int main(int argc, char *argv[]) {
    int num_e; // number of edges
    int num_v; // number of vertices
    int start; // start vertex
    int end; // end vertex
    
    if (argc < 3) {
        printf("Not enough arguments, try again.\n");
        return 1;
    }

    // converts to int
    start = atoi(argv[1]);
    end = atoi(argv[2]);

    scanf("%d", &num_v);
    scanf("%d", &num_e);

    // allocate the necessary space in the struct
    graph g;
    g.num_vertices = num_v;
    g.adj = malloc(num_v*sizeof(edge *));
    g.dist = malloc(num_v*sizeof(int));
    g.parent = malloc(num_v*sizeof(int));

    for (int i = 0; i < num_v; ++i) {
        g.adj[i] = NULL;
    }

    // based on input update
    for (int i = 0; i < num_e; ++i) {
        int u;
        int v;
        int w;

        scanf("%d", &u);
        scanf("%d", &v);
        scanf("%d", &w);

        edge *e1 = malloc(sizeof(edge));
        e1->dest = v;
        e1->weight = w;
        e1->next = g.adj[u];
        g.adj[u] = e1;
    }

    // call dijkstra
    dijkstra(&g, start, end);


    return 0;
}