#include "Motor.h"

Motor::Motor(PinName dirTmp, PinName sleepTmp, PinName stepTmp, PinName enableTmp){
    direction = new DigitalOut(dirTmp, 0);
    sleep = new DigitalOut(sleepTmp, 1);
    step = new DigitalOut(stepTmp, 0);
    enable = new DigitalOut(enableTmp, 0);
}

Motor::Motor(PinName dirTmp, PinName stepTmp, PinName enableTmp){
    direction = new DigitalOut(dirTmp, 0);
    step = new DigitalOut(stepTmp, 0);
    enable = new DigitalOut(enableTmp, 0);
}

void Motor::goToSleep(){
    // Pull pin low to reduce power consumption in the pins
    sleep->write(0);
    ThisThread::sleep_for(1);
}

void Motor::awaken(){
    /* When waking up from sleep the A4988 needs at least
       one millisecond to wake up according to the documentation */
    sleep->write(1);
    ThisThread::sleep_for(1);
}

void Motor::changeDir(){
    // can't use short hand when dealing with pointers
    direction->write(!direction->read());
}

void Motor::turn(uint32_t waitTime){
    step->write(0);
    ThisThread::sleep_for(waitTime);
    step->write(1);
    ThisThread::sleep_for(waitTime);
}

void Motor::enableMotor(){
    // Logic low enables the board
    enable->write(0);
}

void Motor::disableMotor(){
    // Logic high disables the board
    enable->write(1);
}

void Motor::setDirection(int dirTmp){
    direction->write(dirTmp);
}