//
// Created by raphael on 24/11/2024.
//

#include "pedometer.h"
#include "stdlib.h"
#include "plot.h"
#include "filter.h"
#include "fourier.h"
#include "utils.h"
#include "unistd.h"

// Should be a power of two for the fourier transform
#define BUFFER_SIZE 256
#define Fe 120.0f // Hz, the sampling rate
#define Te 1/Fe // s, the sampling period

pedometer_t* load_pedometer() {
    StartSensorListening();
    pedometer_t *pedometer = malloc(sizeof(pedometer_t));
    pedometer->gyroscope_buffer = load_buffer(BUFFER_SIZE);
    pedometer->accelerometer_buffer = load_buffer(BUFFER_SIZE);
    pedometer->fundamental_buffer = load_buffer(BUFFER_SIZE);

    pedometer->gyroscope_data = malloc_empty_array(BUFFER_SIZE);
    pedometer->accelerometer_data = malloc_empty_array(BUFFER_SIZE);

    pedometer->gyroscope_filtered_data = malloc_empty_array(BUFFER_SIZE);
    pedometer->accelerometer_filtered_data = malloc_empty_array(BUFFER_SIZE);

    pedometer->fundamental_data = malloc_empty_array(BUFFER_SIZE);
    pedometer->spectral_data = malloc_empty_array(BUFFER_SIZE/2);

    pedometer->step_sound = LoadSound("beep.wav");

    pedometer->step_counter = 0;

    return pedometer;
}

void unload_pedometer(pedometer_t *pedometer) {
    unload_buffer(pedometer->gyroscope_buffer);
    unload_buffer(pedometer->accelerometer_buffer);
    unload_buffer(pedometer->fundamental_buffer);
    free(pedometer->gyroscope_data);
    free(pedometer->gyroscope_filtered_data);
    free(pedometer->accelerometer_data);
    free(pedometer->fundamental_data);
    free(pedometer->spectral_data);
    free(pedometer->accelerometer_filtered_data);
    UnloadSound(pedometer->step_sound);
    free(pedometer);

    StopSensorListening();
}

void update_pedometer(pedometer_t *pedometer) {
    update_variables(pedometer);
    handle_graphics(pedometer);

}

void update_variables(pedometer_t* pedometer) {
    // add new data to buffers
    add_data(pedometer->gyroscope_buffer, GetGyroscopeX());
    add_data(pedometer->accelerometer_buffer, GetAccelerometerLinearY());

    // retrieve all data from buffers
    get_array(pedometer->gyroscope_buffer, pedometer->gyroscope_data);
    get_array(pedometer->accelerometer_buffer, pedometer->accelerometer_data);
    // update filtered gyroscope
    copy_array_content(pedometer->gyroscope_data, pedometer->gyroscope_filtered_data, BUFFER_SIZE);
    gaussian_low_pass_filter((time_domain_data_t) {pedometer->gyroscope_filtered_data,
                                                   pedometer->gyroscope_buffer->size}, 20);

    copy_array_content(pedometer->accelerometer_data, pedometer->accelerometer_filtered_data,
                       BUFFER_SIZE);
    gate((time_domain_data_t) {pedometer->accelerometer_filtered_data,
                               pedometer->accelerometer_buffer->size}, 0.1f);

    gaussian_low_pass_filter((time_domain_data_t) {pedometer->accelerometer_filtered_data,
                                                   pedometer->accelerometer_buffer->size}, 2);

    bool step = dilate((time_domain_data_t) {pedometer->accelerometer_filtered_data,
                                                 pedometer->accelerometer_buffer->size}, 40);

    if (step) {
        pedometer->step_counter++;
        PlaySound(pedometer->step_sound);
    }

    // update spectral_data
    spectral_decomposition((time_domain_data_t) {pedometer->gyroscope_filtered_data, pedometer->gyroscope_buffer->size}, pedometer->spectral_data);
    //get_array(pedometer->fundamental_buffer, pedometer->fundamental_data);

    //add_data(pedometer->fundamental_buffer, (float ) fundamental_frequency((time_domain_data_t) {pedometer->gyroscope_data, pedometer->gyroscope_buffer->size}));


}

void handle_graphics(pedometer_t *pedometer) {
    // raw gyroscope plot
    plot_v2(pedometer->accelerometer_data, pedometer->gyroscope_buffer->size, (Vector2) {200, 200}, (Vector2) {700, 500});

    // filtered gyroscope plot
    plot_v2(pedometer->accelerometer_filtered_data, pedometer->gyroscope_buffer->size, (Vector2) {200, 800}, (Vector2) {700, 500});

    // spectral plot
    plot_v2(pedometer->spectral_data, pedometer->gyroscope_buffer->size/8, (Vector2) {200, 1400}, (Vector2) {700, 500});

    // fundamental plot
    //plot(pedometer->fundamental_data, pedometer->gyroscope_buffer->size/2, (Vector2) {200, 2000}, (Vector2) {700, 500});

}
