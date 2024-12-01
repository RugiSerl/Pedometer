//
// Created by raphael on 24/11/2024.
//

#ifndef TIPE_MAIN_H
#define TIPE_MAIN_H

#include "raymob.h" // This header can replace 'raylib.h' and includes additional functions related to Android.
#include "pthread.h"
#include "stdlib.h"
#include "buffer.h"

typedef struct arg {
    buffer_t* accelerometerY;
    buffer_t* gyroscopeX;
} arg_t;

#endif //TIPE_MAIN_H
