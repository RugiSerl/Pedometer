//
// Created by raphael on 24/11/2024.
//

#ifndef TIPE_PEDOMETER_H
#define TIPE_PEDOMETER_H

#include "buffer.h"

typedef struct pedometer {
    int step_counter_1;
    int step_counter_2;
    Sound step_sound;

    float level;

    buffer_t *gyroscope_buffer;
    buffer_t *accelerometer_buffer;
    buffer_t *fundamental_buffer;
    buffer_t *amplitude_buffer;

    float *gyroscope_data;
    float *gyroscope_filtered_data;
    float *accelerometer_filtered_data;
    float *accelerometer_data;
    float *fundamental_data;
    float *amplitude_data;
    float *spectral_data;

} pedometer_t;

pedometer_t* load_pedometer();
void unload_pedometer(pedometer_t*);
void update_pedometer(pedometer_t*);
void update_variables(pedometer_t*);
void handle_graphics(pedometer_t*);
void count_step_accelerometer(pedometer_t* pedometer);
void count_step_gyroscope(pedometer_t* pedometer);
#endif //TIPE_PEDOMETER_H
