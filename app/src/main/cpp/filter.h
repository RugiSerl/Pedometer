//
// Created by raphael on 30/11/2024.
//

#ifndef TIPE_FILTER_H
#define TIPE_FILTER_H
#include "fourier.h"
#include "stdbool.h"
void low_pass_filter(time_domain_data_t );
void gaussian_low_pass_filter(time_domain_data_t data, int kernel_radius);
void convolution_high_pass_filter(time_domain_data_t data, int kernel_radius);
bool dilate(time_domain_data_t data, int kernel_radius);
void gate(time_domain_data_t data, float level);

#endif //TIPE_FILTER_H
