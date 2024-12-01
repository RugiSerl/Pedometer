//
// Created by raphael on 30/11/2024.
//
#include "filter.h"
#include "stdlib.h"
#include "raymath.h"


int clamp(int x, int min, int max) {
    if (x>max) return max;
    if (x<min) return min;
    else return x;
}

void low_pass_filter(time_domain_data_t data) {
    float *res = malloc(sizeof(float) * data.n);
    res[0] = 0;
    for (int i = 0; i<data.n-1; i++) {
        res[i + 1] = res[i] + (data.samples[i] - res[i]) * 0.1f;
    }
    for (int i = 0; i<data.n-1; i++) {
        data.samples[i] = res[i];
    }
    free(res);
}

void gaussian_filter(time_domain_data_t data) {
    float *res = malloc(sizeof(float) * data.n);
    int kernel_radius = 20;
    float ker_radius_f = (float) kernel_radius;
    for (int i = 0; i<data.n-1; i++) {
        res[i] = 0;
    }

    float coef_sum;
    float coef;
    for (int i = 0; i<data.n-1; i++) {
        coef_sum = 0;
        for (int j = clamp(i-kernel_radius, 0, data.n); j < clamp(i+kernel_radius, 0, data.n); j++) {
            float x = (float ) (i-j);
            coef = expf(- x*x / (ker_radius_f*ker_radius_f));
            coef_sum += coef;
            res[i] += coef*data.samples[j];
        }
        if (coef_sum != 0) res[i] /= coef_sum;

    }

    for (int i = 0; i<data.n-1; i++) {
        data.samples[i] = res[i];
    }
    free(res);
}

