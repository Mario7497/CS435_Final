#include "mbed.h"
#include "rtos.h"
#include "Motor.h"
#include "Joystick.h"
#include "LightSensor.h"
#include "ArrayAverager.h"
#include <cstdio>
#include <vector>
#include <string>

#define DIRECTION_A D2
#define DIRECTION_B D5
#define STEP_A D3
#define STEP_B D6
#define SLEEP D4
#define ENABLE_A D7
#define ENABLE_B D8
#define PULSE_TIME 5
#define BUTTON D9
#define X_AXIS_PIN A5
#define Y_AXIS_PIN A4
#define TOP_LEFT A0
#define TOP_RIGHT A1
#define BOTTOM_LEFT A2
#define BOTTOM_RIGHT A3
#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1

// Serial setup
Serial pc(USBTX,USBRX);
// End of Serial setup

// Motor setup
Motor theta(DIRECTION_A, SLEEP, STEP_A, ENABLE_A);
Motor phi(DIRECTION_B, STEP_B, ENABLE_B);
void motorA();
void motorB();
// End of Motor Setup

// Joystick setup
Joystick joystick(X_AXIS_PIN, Y_AXIS_PIN);
void monitorJoystick();
// End of Joystick setup

// Light Sensor setup
LightSensor lightSensor(TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT);
void showSensorData();
void lightMotorControlX();
void lightMotorControlY();
// End of Light Sensor setup

int main()
{
    Thread photoArrayThread;
    Thread joystickThread;
    Thread tiltThread;
    Thread yawThread;
    Thread monitorX;
    Thread monitorY;

    //photoArrayThread.start(showSensorData);
    //joystickThread.start(monitorJoystick);
    tiltThread.start(motorA);
    yawThread.start(motorB);
    //monitorX.start(lightMotorControlX);
    //monitorY.start(lightMotorControlY);

    while (true) {
      ThisThread::sleep_for(500);
      }

}

void motorA(){
    float x = joystick.getXAxis();;
    while (true) {
        x = joystick.getXAxis();
        if(0.4 < x && x < 0.6){
            ThisThread::sleep_for(1);
        }else if (x < 0.4) {
            theta.setDirection(CLOCKWISE);
            theta.turn(PULSE_TIME);
        }else {
            theta.setDirection(COUNTER_CLOCKWISE);
            theta.turn(PULSE_TIME);
        }
    }
}

void motorB(){
    float y = joystick.getYAxis();
    while (true) {
        y = joystick.getYAxis();
        if(0.4 < y && y < 0.6){
            ThisThread::sleep_for(10);
        }else if (y < 0.4) {
            phi.setDirection(CLOCKWISE);
            phi.turn(PULSE_TIME);
        }else {
            phi.setDirection(COUNTER_CLOCKWISE);
            phi.turn(PULSE_TIME);
        }
    }
}

void showSensorData() {
  short arraySize = 4;
  float photoValues[arraySize];
  ArrayAverager arrayAverager(1);
  float* avgPhotoValues;

  while (true) {
    for (int i = 0; i < arraySize; i++) {
      photoValues[i] =
          lightSensor.getPhotoValue_f((LightSensor::photoElement)i);
    }
    
    avgPhotoValues = arrayAverager.updateArray(photoValues);

    pc.printf("Photo resister 0 = %4.4f\n"  , avgPhotoValues[0]);
    pc.printf("Photo resister 1 = %4.4f\n"  , avgPhotoValues[1]);
    pc.printf("Photo resister 2 = %4.4f\n"  , avgPhotoValues[2]);
    pc.printf("Photo resister 3 = %4.4f\n\n", avgPhotoValues[3]);
    ThisThread::sleep_for(1000);
  }
}

void monitorJoystick(){
    while(true) {
        pc.printf("\nX position = %4.5f\n", joystick.getXAxis());
        pc.printf("Y position = %4.5f\n\n", joystick.getYAxis());
        ThisThread::sleep_for(500);
    }
}

void lightMotorControlX(){
    short arraySize = 4;
    float photoValues[arraySize];
    ArrayAverager arrayAverager(1);
    float* avg;

    float R0_t = 0.914;
    float R1_t = 0.977;
    float R2_t = 0.965;
    float R3_t = 0.960;

    while (true) {
        for (int i = 0; i < arraySize; i++) {
        photoValues[i] =
            lightSensor.getPhotoValue_f((LightSensor::photoElement)i);
        }
        avg = arrayAverager.updateArray(photoValues);

        if(avg[1] > R1_t && avg[3] > R3_t){
            theta.setDirection(0);
            theta.turn(PULSE_TIME);
        } else if (avg[0] > R0_t && avg[2] > R2_t) {
            theta.setDirection(1);
            theta.turn(PULSE_TIME);
        }else {
            ThisThread::sleep_for(250);
        }
        
    }
}

void lightMotorControlY(){
        short arraySize = 4;
    float photoValues[arraySize];
    ArrayAverager arrayAverager(1);
    float* avg;

    float R0_t = 0.914;
    float R1_t = 0.977;
    float R2_t = 0.965;
    float R3_t = 0.960;

    while (true) {
        for (int i = 0; i < arraySize; i++) {
        photoValues[i] =
            lightSensor.getPhotoValue_f((LightSensor::photoElement)i);
        }
        avg = arrayAverager.updateArray(photoValues);

        if(avg[1] > R1_t && avg[0] > R0_t){
            phi.setDirection(0);
            phi.turn(PULSE_TIME);
        } else if (avg[3] > R0_t && avg[2] > R2_t) {
            phi.setDirection(1);
            phi.turn(PULSE_TIME);
        }else {
            ThisThread::sleep_for(250);
        }
        
    }
}