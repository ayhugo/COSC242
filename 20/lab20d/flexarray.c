#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

void insertion_sort(int *a, int n) {
    int p = 0;
    int key = 0;
    int temp = 0;
    for (p = 1; p < n; p++) {
        key = p;
        while (key > 0 &&  a[key] < a[key - 1]) {
            temp = a[key];
            a[key] = a[key - 1];
            a[key - 1] = temp;
            key--;
        }
        if (p == ((n / 2) - 1)) {
            for (key = 0; key < n; key++) {
                fprintf(stderr, "%d\n", a[key]);
            }
        }
    }
}

void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s) {
    p = realloc(p, s);
    if (NULL == p) {
        fprintf(stderr, "Memory realocation failed!");
        exit(EXIT_FAILURE);
    }
    return p;
}

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result ->items[0]);
    return result;
}

void flexarray_append(flexarray f, int num) {
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f) {
    int i;

    for (i = 0; i < f->itemcount; i++) {
        fprintf(stdout, "%d\n", f->items[i]);
    }
}

void flexarray_sort(flexarray f) {
    insertion_sort(f->items, f->itemcount);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}
