#include "Joystick.h"
#include <cstdio>

Joystick::Joystick(PinName xPin, PinName yPin){
    xAxis  = new AnalogIn(xPin);
    yAxis  = new AnalogIn(yPin);

}

float Joystick::getXAxis(){
    return xAxis->read();
}

float Joystick::getYAxis(){
    return yAxis->read();
}

