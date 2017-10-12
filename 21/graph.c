#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mylib.h"
#include "queue.h"

typedef enum { UNVISITED, VISITED_SELF, VISITED_DESCENDANTS } state_t;

/* create a graph struct. */
struct graphrec {
    int **edges;
    int *predecessor;
    int *distance;
    state_t *state;
    int size;
};

/*
 * creates a new and initialised graph with int vertices. Using emalloc to
 * allocation memory for.
 * PARAMS: takes an integer argument to say how many vertices
 * the graph has.
 * RETURN: an initialised graph
 */
graph graph_new(int vertices) {
    int i;
    int j;
    graph result = emalloc(sizeof *result);
    result->size = vertices;
    result->edges = emalloc(result->size * sizeof result->edges[0]);
    result->predecessor = emalloc(result->size * sizeof result->predecessor[0]);
    result->distance = emalloc(result->size * sizeof result->distance[0]);
    result->state = emalloc(result->size * sizeof result->state[0]);
    for (i = 0; i < result->size; i++) {
        result->edges[i] = emalloc(result->size * sizeof result->edges[0][0]);
        result->predecessor[i] = 0;
        result->distance[i] = 0;
        result->state[i] = UNVISITED;
        for (j = 0; j < result->size; j++) {
            result->edges[i][j] = 0;
        }
    }
    return result;
}

/* funciton adds values to the boolean matrix edges.
 * PARAMS: a grah g to add edges too.
 *         two integer values that are edges to each other (v1 and v2).
 */
void graph_add_edge(graph g, int v1, int v2) {
    g->edges[v1][v2] = 1;
    g->edges[v2][v1] = 1;
}

/* function that performs a breadth-first search on a graph.
 * PARAMS: a graph g for the bfs to be performed on.
 *         an integer source value that will be the start point
 *         for the search. Use 1 in the main (graph-test.c)
 */
void graph_bfs(graph g, int source) { /* source = vertex we find distances from */
    queue q = queue_new();
    int v;
    int u;
    /* for each vertex in the graph
     * Set state as unvisited
     * set distance to infinity
     * set predecessor as non-existent
     */
    for (v = 0; v < g->size; v++) {
        g->state[v] = UNVISITED;
        g->distance[v] = -1;
        g->predecessor[v] = -1;
    }
    /* set source state to visisted_self
     * Set source distance to 0
     * add source to the queue
     */
    g->state[source] = VISITED_SELF;
    g->distance[source] = 0;
    enqueue(q, source);

    /* While the queue isn't empty
     * set vertex u to be a vertex removed from queue */
    while (queue_size(q) != 0) {
        u = dequeue(q);

        /* for each vertex v adjacent to u, that has not been visited
        *  Set its state to process of being visited
        *  Set its distance to be 1 + the distance to u
        *  set its predecessor to u
        *  add v to queue
        */
        for (v = 0; v < g->size; v++) {
            if (g->edges[v][u] == 1 && g->state[v] == UNVISITED) {
                g->state[v] = VISITED_SELF;
                g->distance[v] = 1 + g->distance[u];
                g->predecessor[v] = u;
                enqueue(q, v);
            }
        }
        /*set u's state to visited_descendants */
        g->state[u] = VISITED_DESCENDANTS;
    }
    queue_free(q);
}

/* prints out which nodes are adjacent to eachother, a vertices distance
 * and predecessor.
 * PARAMS: a graph g that will be printed.
 */
void graph_print(graph g) {
    int i;
    int j = 0;
    int count = 0;
    printf("adjacency list:\n");
    for (i = 0; i < g->size; i++) {
        printf("%d | ", i);
        count = 0;
        for (j = 0; j < g->size; j++) {
            if (g->edges[i][j] == 1) {
                if (count == 0) {
                    printf("%d", j);
                    count++;
                }else {
                    printf(", %d", j);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("vertex distance pred\n");
    for (i = 0; i < g->size; i++) {
        printf("%4d %6d %6d\n", i, g->distance[i], g->predecessor[i]);
    }
}

/* frees a graph g and all its memory allocations.
 * PARAMS: a graph g to be freed.
 */
void graph_free(graph g) {
    int i;
    for (i = 0; i < g->size; i++) {
            free(g->edges[i]);
    }
    free(g->predecessor);
    free(g->state);
    free(g->distance);
    free(g->edges);
    free(g);
}
