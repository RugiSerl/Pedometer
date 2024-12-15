//
// Created by raphael on 01/12/2024.
//

#ifndef TIPE_UTILS_H
#define TIPE_UTILS_H


float max_array(float* t, int n);
float max_array_range(float* array, int n, int i, int j);
float max_array_abs(float* t, int n);
int clamp(int x, int min, int max);
void copy_array_content(float*, float*, int n);
float* malloc_empty_array(int n);

float absf(float );

#endif //TIPE_UTILS_H
