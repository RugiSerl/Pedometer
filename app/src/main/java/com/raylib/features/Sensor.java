/*
 *  raymob License (MIT)
 *
 *  Copyright (c) 2023-2024 Le Juez Victor
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

package com.raylib.features;

import android.content.Context;
import android.hardware.SensorEvent;
import android.hardware.SensorManager;

public class Sensor implements android.hardware.SensorEventListener {

    private SensorManager sensorManager;
    private android.hardware.Sensor accelerometer;
    private android.hardware.Sensor accelerometerLinear;
    private android.hardware.Sensor gyroscope;
    private android.hardware.Sensor magnetometer;
    private float[] accelerometerValues = new float[3]; // To store the axis values (x, y, z)
    private float[] accelerometerLinearValues = new float[3]; // To store the axis values (x, y, z)
    private float[] gyroscopeValues = new float[3]; // To store the axis values (x, y, z)
    private float[] magnetometerValues = new float[3]; // To store the axis values (x, y, z)

    public Sensor(Context context) {
        sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
        if (sensorManager != null) {
            accelerometer = sensorManager.getDefaultSensor(android.hardware.Sensor.TYPE_ACCELEROMETER);
            accelerometerLinear = sensorManager.getDefaultSensor(android.hardware.Sensor.TYPE_LINEAR_ACCELERATION);
            gyroscope = sensorManager.getDefaultSensor(android.hardware.Sensor.TYPE_GYROSCOPE);
            magnetometer = sensorManager.getDefaultSensor(android.hardware.Sensor.TYPE_MAGNETIC_FIELD);
        }
    }

    // Method to start listening to the accelerometer
    public void startListening() {
        if (accelerometer != null) {
            sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_FASTEST);
            sensorManager.registerListener(this, accelerometerLinear, SensorManager.SENSOR_DELAY_FASTEST);
            sensorManager.registerListener(this, gyroscope, SensorManager.SENSOR_DELAY_FASTEST);
            sensorManager.registerListener(this, magnetometer, SensorManager.SENSOR_DELAY_FASTEST);
        }
    }

    // Method to stop listening to the accelerometer
    public void stopListening() {
        sensorManager.unregisterListener(this);
    }

    // Method to get the value of the X-axis
    public float getAccelerometerX() {
        return accelerometerValues[0];
    }

    // Method to get the value of the Y-axis
    public float getAccelerometerY() {
        return accelerometerValues[1];
    }

    // Method to get the value of the Z-axis
    public float getAccelerometerZ() {
        return accelerometerValues[2];
    }

    // Method to get the value of the X-axis
    public float getAccelerometerLinearX() {
        return accelerometerLinearValues[0];
    }

    // Method to get the value of the Y-axis
    public float getAccelerometerLinearY() {
        return accelerometerLinearValues[1];
    }

    // Method to get the value of the Z-axis
    public float getAccelerometerLinearZ() {
        return accelerometerLinearValues[2];
    }

    // Method to get the value of the X-axis
    public float getGyroscopeX() {
        return gyroscopeValues[0];
    }

    // Method to get the value of the Y-axis
    public float getGyroscopeY() {
        return gyroscopeValues[1];
    }

    // Method to get the value of the Z-axis
    public float getGyroscopeZ() {
        return gyroscopeValues[2];
    }// Method to get the value of the X-axis
    public float getMagnetometerX() {
        return gyroscopeValues[0];
    }

    // Method to get the value of the Y-axis
    public float getMagnetometerY() {
        return gyroscopeValues[1];
    }

    // Method to get the value of the Z-axis
    public float getMagnetometerZ() {
        return gyroscopeValues[2];
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == android.hardware.Sensor.TYPE_ACCELEROMETER) {
            accelerometerValues[0] = event.values[0]; // X-axis
            accelerometerValues[1] = event.values[1]; // Y-axis
            accelerometerValues[2] = event.values[2]; // Z-axis
        } else if (event.sensor.getType() == android.hardware.Sensor.TYPE_GYROSCOPE) {
            gyroscopeValues[0] = event.values[0]; // X-axis
            gyroscopeValues[1] = event.values[1]; // Y-axis
            gyroscopeValues[2] = event.values[2]; // Z-axis
        } else if (event.sensor.getType() == android.hardware.Sensor.TYPE_MAGNETIC_FIELD) {
            magnetometerValues[0] = event.values[0]; // X-axis
            magnetometerValues[1] = event.values[1]; // Y-axis
            magnetometerValues[2] = event.values[2]; // Z-axis
        } else if (event.sensor.getType() == android.hardware.Sensor.TYPE_LINEAR_ACCELERATION) {
            accelerometerLinearValues[0] = event.values[0]; // X-axis
            accelerometerLinearValues[1] = event.values[1]; // Y-axis
            accelerometerLinearValues[2] = event.values[2]; // Z-axis
        }
    }

    @Override
    public void onAccuracyChanged(android.hardware.Sensor sensor, int accuracy) {
        // Do nothing in case of sensor accuracy change
    }
}
