//
// Created by raphael on 01/12/2024.
//

#include "utils.h"

float absf(float x) {
    return (x >= 0) ? x : -x;
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
