#include "fourier.h"
#include "stdlib.h"
#include "math.h"
#include "utils.h"


// Straightforward implementation of DFT.
// Don't forget to free the data returned.
frequency_domain_data_t* discrete_fourier_transform(time_domain_data_t data) {
    frequency_domain_data_t *res = malloc(sizeof(frequency_domain_data_t));
    res->n = data.n;
    res->coefficients = malloc(sizeof(complex float) * res->n);
    for (int coefficient = 0; coefficient<res->n; coefficient++) {
        res->coefficients[coefficient] = 0;
        for (int sample = 0; sample<res->n; sample++) {
            res->coefficients[coefficient] +=
                    data.samples[sample] * cexpf(-2 * I * M_PI * coefficient * sample / res->n);
        }
    }
    return res;
}
//--------------------------------------------
// Cooley Tuckey divide and conquer algorithm.

// Actual recursive function doing the algorithm.
// We need to suppose the size of the data is a power of two, so always even except for 1.
// I repeat, the size of the data MUST be a power of two, else it won't work.
void fft(time_domain_data_t data, frequency_domain_data_t res, complex float omega) {
    // Base case
    if (data.n==1) {
        res.coefficients[0] = data.samples[0];
        return;
    }

    // Divide part
    complex float omega_squared = omega * omega;
    float *even_samples = malloc(sizeof(float) * data.n / 2);
    float *odd_samples = malloc(sizeof(float) * data.n / 2);
    complex float *even_results = malloc(sizeof(complex float) * data.n / 2);
    complex float *odd_results = malloc(sizeof(complex float) * data.n / 2);
    for (int i = 0; i<data.n; i++) {
        if (i%2==0) even_samples[i / 2] = data.samples[i];
        else odd_samples[i / 2] = data.samples[i];
    }
    fft((time_domain_data_t) {even_samples, data.n / 2}, (frequency_domain_data_t) {even_results, data.n / 2}, omega_squared);
    fft((time_domain_data_t) {odd_samples, data.n / 2}, (frequency_domain_data_t) {odd_results, data.n / 2}, omega_squared);

    // Conquer part
    complex float omega_power_k = 1;
    for (int k = 0; k<data.n/2; k++) {
        res.coefficients[k] = even_results[k] + omega_power_k * odd_results[k];
        res.coefficients[k + data.n/2] = even_results[k] - omega_power_k * odd_results[k];

        omega_power_k *= omega; // to avoid to call the pow function each time
    }

    // Important: free the data we created in this call !!
    free(even_samples);
    free(odd_samples);
    free(even_results);
    free(odd_results);

}

// main function
frequency_domain_data_t* fast_fourier_transform(time_domain_data_t data) {
    frequency_domain_data_t *res = malloc(sizeof(frequency_domain_data_t));
    res->n = data.n;
    res->coefficients = malloc(sizeof(complex float) * res->n);
    fft(data, *res, cexpf(-2*M_PI*I/data.n));
    return res;
}

// Get Spectral decomposition by calculating the abs of the coefficients.
// Be careful, the size of the array is n/2, because we don't need the second half of data which is just the same data mirrored.
void spectral_decomposition(time_domain_data_t signal, float* res) {
    frequency_domain_data_t *coeffs = fast_fourier_transform(signal);


    for (int i = 0; i < coeffs->n/2; i++) {
        res[i] = cabsf(coeffs->coefficients[i]);
    }

    free(coeffs->coefficients);
    free(coeffs);

}

int fundamental_frequency(time_domain_data_t signal) {
    float *frequencies = malloc(signal.n / 2);
    spectral_decomposition(signal, frequencies);
    float max = max_array(frequencies, signal.n / 2);
    for (int i = 0; i<signal.n/2; i++) {
        if (frequencies[i] > max * 0.5f) {
            free(frequencies);
            return i;
        }
    }
    free(frequencies);

}


