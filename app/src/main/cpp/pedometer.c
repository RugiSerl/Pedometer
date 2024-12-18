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
#define BUFFER_SIZE 512
#define Fe 120.0f // Hz, the sampling rate
#define Te 1/Fe // s, the sampling period

pedometer_t* load_pedometer() {
    StartSensorListening();
    pedometer_t *pedometer = malloc(sizeof(pedometer_t));
    pedometer->gyroscope_buffer = load_buffer(BUFFER_SIZE);
    pedometer->accelerometer_buffer = load_buffer(BUFFER_SIZE);
    pedometer->fundamental_buffer = load_buffer(BUFFER_SIZE);
    pedometer->amplitude_buffer = load_buffer(BUFFER_SIZE);

    pedometer->gyroscope_data = malloc_empty_array(BUFFER_SIZE);
    pedometer->accelerometer_data = malloc_empty_array(BUFFER_SIZE);

    pedometer->gyroscope_filtered_data = malloc_empty_array(BUFFER_SIZE);
    pedometer->accelerometer_filtered_data = malloc_empty_array(BUFFER_SIZE);

    pedometer->fundamental_data = malloc_empty_array(BUFFER_SIZE);
    pedometer->spectral_data = malloc_empty_array(BUFFER_SIZE/2);
    pedometer->amplitude_data = malloc_empty_array(BUFFER_SIZE/2);

    pedometer->step_sound = LoadSound("beep.wav");

    pedometer->step_counter_1 = 0;
    pedometer->step_counter_2 = 0;
    pedometer->level = 0.5f;

    return pedometer;
}

void unload_pedometer(pedometer_t *pedometer) {
    unload_buffer(pedometer->gyroscope_buffer);
    unload_buffer(pedometer->accelerometer_buffer);
    unload_buffer(pedometer->fundamental_buffer);
    unload_buffer(pedometer->amplitude_buffer);
    free(pedometer->gyroscope_data);
    free(pedometer->gyroscope_filtered_data);
    free(pedometer->accelerometer_data);
    free(pedometer->fundamental_data);
    free(pedometer->spectral_data);
    free(pedometer->accelerometer_filtered_data);
    free(pedometer->amplitude_data);
    UnloadSound(pedometer->step_sound);
    free(pedometer);

    StopSensorListening();
}

void update_pedometer(pedometer_t *pedometer) {
    update_variables(pedometer);
    count_step_gyroscope(pedometer);
    count_step_accelerometer(pedometer);
    handle_graphics(pedometer);

}

void count_step_gyroscope(pedometer_t* pedometer) {
    if (pedometer->gyroscope_filtered_data[20]>pedometer->level && pedometer->gyroscope_filtered_data[21]<=pedometer->level) {
        pedometer->step_counter_1++;
    }
}

void count_step_accelerometer(pedometer_t* pedometer) {
    gate((time_domain_data_t) {pedometer->accelerometer_filtered_data,
                               pedometer->accelerometer_buffer->size}, 0.7f);

    bool step = dilate((time_domain_data_t) {pedometer->accelerometer_filtered_data,
                                             pedometer->accelerometer_buffer->size}, 40);
    if (step) {
        pedometer->step_counter_2++;
    }
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

    gaussian_low_pass_filter((time_domain_data_t) {pedometer->accelerometer_filtered_data,
                                                   pedometer->accelerometer_buffer->size}, 2);


    // update spectral_data
    spectral_decomposition((time_domain_data_t) {pedometer->gyroscope_filtered_data, pedometer->gyroscope_buffer->size}, pedometer->spectral_data);
    //get_array(pedometer->fundamental_buffer, pedometer->fundamental_data);

    //add_data(pedometer->fundamental_buffer, (float ) fundamental_frequency((time_domain_data_t) {pedometer->gyroscope_data, pedometer->gyroscope_buffer->size}));


}

void handle_graphics(pedometer_t *pedometer) {
    // plot gyroscope && level
    float *level_array = malloc_filled_array(pedometer->gyroscope_buffer->size, pedometer->level);
    float **plotted = malloc(sizeof(float *) * 2);
    plotted[0] = level_array;
    plotted[1] = pedometer->gyroscope_filtered_data;
    // raw gyroscope plot
    plot_v2((Vector2) {200, 500}, (Vector2) {700, 500}, pedometer->gyroscope_buffer->size, 2, plotted);
    free(level_array);

    // plot accelerometer and dilated
    plotted[0] = pedometer->accelerometer_data;
    plotted[1] = pedometer->accelerometer_filtered_data;
    plot_v2((Vector2) {200, 1100}, (Vector2) {700, 500}, pedometer->gyroscope_buffer->size, 2, plotted);


    free(plotted);
}
