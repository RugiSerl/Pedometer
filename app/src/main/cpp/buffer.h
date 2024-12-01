//
// Created by raphael on 24/11/2024.
//

#ifndef TIPE_BUFFER_H
#define TIPE_BUFFER_H

#include "raymob.h"
#include "stdlib.h"

// Implementation of a circular buffer
typedef struct buffer {
    float *data; // array of the data contained
    int size; // size of the array stored
    int index; // index of the next element to be added
}buffer_t;

// Load empty buffer
buffer_t* load_buffer(int size);

// Unload buffer from memory to avoid segfault
void unload_buffer(buffer_t*);

// Add data to buffer
void add_data(buffer_t*, float);

// Get the data from the most recent recorded element.
float get_data(buffer_t *, int);


void get_array(buffer_t*, float*);



#endif //TIPE_BUFFER_H
