//
// Created by raphael on 01/12/2024.
//

#include "utils.h"
#include "assert.h"
#include "stdlib.h"

float absf(float x) {
    return (x >= 0) ? x : -x;
}

int clamp(int x, int min, int max) {
    if (x>max) return max;
    if (x<min) return min;
    else return x;
}

float max_array_abs(float * array, int size) {
    float max = array[0];
    for (int i = 0; i < size; i++) {
        if (absf(array[i])>max) max = absf(array[i]);
    }
    return max;
}

float max_array(float* array, int n) {
    float m = 0;
    for (int i = 0; i < n; i++) {
        if (array[i]>m) m = array[i];
    }
    return m;
}

float max_array_range(float* array, int n, int i, int j) {
    float m = 0;
    assert(i>=0 && j<n);
    for (int k = i; k < j; k++) {
        if (array[k]>m) m = array[k];
    }
    return m;
}

float* malloc_empty_array(int n) {
    float *t = malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++) {
        t[i] = 0;
    }
    return t;
}


void copy_array_content(float *src, float *dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}


