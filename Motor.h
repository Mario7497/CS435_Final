/*
This Driver impliments the A4988 Stepper motor driver board
*/

#include "mbed.h"

#ifndef MOTOR_H
#define MOTOR_H

class Motor{
    private:
        DigitalOut *direction;
        DigitalOut *sleep;
        DigitalOut *step;
        DigitalOut *enable;
    public:
        Motor(PinName dirTmp, PinName sleepTmp, PinName stepTmp, PinName enableTmp);
        Motor(PinName dirTmp, PinName stepTmp, PinName enableTmp);
        void awaken();
        void goToSleep();
        void changeDir();
        void setDirection(int dirTmp);
        void turn(uint32_t waitTime);
        void enableMotor();
        void disableMotor();

};
#endif