//
// Created by raphael on 27/11/2024.
//
#include "plot.h"
#include "raymob.h"
#include "raymath.h"
#include "utils.h"

void plot(float* array, int array_size, Vector2 position, Vector2 size) {
    DrawRectangleV(position, size, LIGHTGRAY);

    float max = max_array_abs(array, array_size);
    float data;
    for (int i = 0; i < array_size; i++) {
        data = -array[i];
        if (data>0) {
            DrawRectangleV((Vector2) {position.x + size.x / array_size * i, position.y + size.y / 2},(Vector2) {size.x / array_size, size.y * data/max/2}, RED);
        } else {
            DrawRectangleV((Vector2) {position.x + size.x / array_size * i, position.y + size.y / 2 + size.y * data/max/2},(Vector2) {size.x / array_size, -size.y * data/max/2}, RED);
        }

    }
}

void plot_v2(float* array, int array_size, Vector2 position, Vector2 size) {
    DrawRectangleV(position, size, LIGHTGRAY);

    float max = max_array_abs(array, array_size);
    Vector2 start_pos;
    Vector2 end_pos;
    float radius = size.x / array_size * 2;


    for (int i = 0; i < array_size-1; i++) {
        start_pos = (Vector2){position.x + size.x / array_size * i, position.y + size.y / 2 *(1-array[i]/max)};
        end_pos = (Vector2){position.x + size.x / array_size * (i+1), position.y + size.y / 2 *(1-array[i+1]/max)};

        // Linear interpolation
        for (float t = 0; t<1; t+= radius/Vector2Distance(start_pos, end_pos)) {
            DrawCircleV(Vector2Add(Vector2Scale(start_pos, (1-t)), Vector2Scale(end_pos, t)), radius, BLUE);

        }

    }
}