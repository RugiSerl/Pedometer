//
// Created by raphael on 24/11/2024.
//

#include "pedometer.h"
#include "stdlib.h"
#include "plot.h"
#include "filter.h"
#include "fourier.h"

// Should be a power of two for the fourier transform
#define BUFFER_SIZE 512

pedometer_t* load_pedometer() {
    StartSensorListening();
    pedometer_t *pedometer = malloc(sizeof(pedometer_t));
    pedometer->gyroscope_buffer = load_buffer(BUFFER_SIZE);
    pedometer->accelerometer_buffer = load_buffer(BUFFER_SIZE);
    pedometer->gyroscope_data = malloc(sizeof(float) * BUFFER_SIZE);
    pedometer->accelerometer_data = malloc(sizeof(float) * BUFFER_SIZE);
    pedometer->fundamental_buffer = load_buffer(BUFFER_SIZE);
    pedometer->fundamental_data = malloc(sizeof(float) * BUFFER_SIZE);


    pedometer->step_counter = 0;


    return pedometer;
}

void unload_pedometer(pedometer_t *pedometer) {
    unload_buffer(pedometer->gyroscope_buffer);
    unload_buffer(pedometer->accelerometer_buffer);
    unload_buffer(pedometer->fundamental_buffer);
    free(pedometer->gyroscope_data);
    free(pedometer->accelerometer_data);
    free(pedometer->fundamental_data);

    free(pedometer);

    StopSensorListening();
}

void update_pedometer(pedometer_t *pedometer) {

    add_data(pedometer->gyroscope_buffer, GetGyroscopeX());
    add_data(pedometer->accelerometer_buffer, GetAccelerometerY());

    //TraceLog(LOG_INFO, "%f", GetGyroscopeX());

    if (get_data(pedometer->gyroscope_buffer, 0) > 0 &&
        get_data(pedometer->gyroscope_buffer, 1) <= 0) {
        pedometer->step_counter++;
    }

    get_array(pedometer->gyroscope_buffer, pedometer->gyroscope_data);
    get_array(pedometer->accelerometer_buffer, pedometer->accelerometer_data);
    get_array(pedometer->fundamental_buffer, pedometer->fundamental_data);

    // raw gyroscope plot
    plot_v2(pedometer->gyroscope_data, pedometer->gyroscope_buffer->size, (Vector2) {200, 200}, (Vector2) {700, 500});

    // filtered gyroscope plot
    gaussian_filter((time_domain_data_t){pedometer->gyroscope_data, pedometer->gyroscope_buffer->size});
    plot_v2(pedometer->gyroscope_data, pedometer->gyroscope_buffer->size, (Vector2) {200, 800}, (Vector2) {700, 500});

    // spectral plot
    float *spectral_view = spectral_decomposition((time_domain_data_t) {pedometer->gyroscope_data, pedometer->gyroscope_buffer->size});
    plot_v2(spectral_view, pedometer->gyroscope_buffer->size/2, (Vector2) {200, 1400}, (Vector2) {700, 500});

    // fundamental plot
    add_data(pedometer->fundamental_buffer, (float ) fundamental_frequency((time_domain_data_t) {pedometer->gyroscope_data, pedometer->gyroscope_buffer->size}));
    plot_v2(pedometer->fundamental_data, pedometer->gyroscope_buffer->size/2, (Vector2) {200, 2000}, (Vector2) {700, 500});



    free(spectral_view);






}
