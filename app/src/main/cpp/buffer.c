//
// Created by raphael on 24/11/2024.
//
#include "buffer.h"



buffer_t* load_buffer(int size) {
    buffer_t *buffer = malloc(sizeof(buffer_t));
    buffer->data = malloc(sizeof(float) * size);
    buffer->index = 0;
    buffer->size = size;

    return buffer;
}

void unload_buffer(buffer_t* buffer) {
    free(buffer->data);
    free(buffer);
}

void add_data(buffer_t* buffer, float data) {
    buffer->data[buffer->index] = data;
    buffer->index = (buffer->index + 1) % buffer->size;

}

float get_data(buffer_t *buffer, int age) {
    return buffer->data[(buffer->index - age - 1 + buffer->size) % buffer->size];
}


// you need to allocate res with the right size, the size of the buffer
void get_array(buffer_t* buffer, float* res) {
    for (int i = 0; i<buffer->size; i++) {
        res[i] = get_data(buffer, i);
    }
}

