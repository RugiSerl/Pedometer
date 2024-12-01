//
// Created by raphael on 27/11/2024.
//

#ifndef TIPE_FOURIER_H
#define TIPE_FOURIER_H

#include "complex.h"

typedef struct time_domain_data {
    float* samples;
    int n;
} time_domain_data_t;

typedef struct frequency_domain_data {
    float complex* coefficients;
    int n;
} frequency_domain_data_t;

frequency_domain_data_t* discrete_fourier_transform(time_domain_data_t);
frequency_domain_data_t * fast_fourier_transform(time_domain_data_t);
float* spectral_decomposition(time_domain_data_t);
int fundamental_frequency(time_domain_data_t);



#endif //TIPE_FOURIER_H
