#include "mbed.h"

#define ARRAY_SIZE 4

#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

class LightSensor{
    private:
        AnalogIn *photoArray[ARRAY_SIZE];
    public:
        enum photoElement {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
        LightSensor(PinName photo0, PinName photo1, PinName photo2, PinName photo3);
        float getPhotoValue_f(photoElement element);
        unsigned short getPhotoValue_u16(photoElement element);

};

#endif