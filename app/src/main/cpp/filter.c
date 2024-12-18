//
// Created by raphael on 30/11/2024.
//
#include "filter.h"
#include "stdlib.h"
#include "raymath.h"
#include "utils.h"



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

void gaussian_low_pass_filter(time_domain_data_t data, int kernel_radius) {
    float *res = malloc_empty_array(data.n);
    float ker_radius_f = (float) kernel_radius;

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

    copy_array_content(res, data.samples, data.n);
    free(res);
}


void convolution_high_pass_filter(time_domain_data_t data, int kernel_radius) {
    float *res = malloc(sizeof(float) * data.n);
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
            coef = 1;
            coef_sum += coef;
            res[i] += coef*data.samples[j];
        }
        if (coef_sum != 0) res[i] /= coef_sum;

    }

    copy_array_content(res, data.samples, data.n);
    free(res);
}

void gate(time_domain_data_t data, float level) {
    for (int i = 0; i<data.n-1; i++) {
        data.samples[i] = (absf(data.samples[i]) > level) ? data.samples[i] : 0;
    }
}




bool dilate(time_domain_data_t data, int kernel_radius) {
    float *res = malloc(sizeof(float) * data.n);
    float ker_radius_f = (float) kernel_radius;
    for (int i = 0; i<data.n; i++) {
        res[i] = max_array_range(data.samples, data.n, maxi(i - kernel_radius, 0),
                                 mini(i + kernel_radius, data.n - 1));
    }
    bool reached = (res[kernel_radius] == data.samples[kernel_radius] && res[kernel_radius]!=0);
    copy_array_content(res, data.samples, data.n);
    free(res);
    return reached;
}


