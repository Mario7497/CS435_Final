#include "mbed.h"


#ifndef JOYSTICK_H
#define JOYSTICK_H

class Joystick{
    private:
        AnalogIn  *xAxis;
        AnalogIn  *yAxis;
        int motorDirectionA  = 0;
        int motorDirectionB  = 0;        
        
    public:
        Joystick(PinName xPin, PinName yPin);

        float getXAxis();
        float getYAxis();
};

#endif