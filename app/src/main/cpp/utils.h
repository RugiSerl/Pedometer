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
float* malloc_filled_array(int n, float value);
float maxf(float x, float y);
float get_max_arrays(int array_size, int array_count, float** arrays);
float absf(float );

#endif //TIPE_UTILS_H
