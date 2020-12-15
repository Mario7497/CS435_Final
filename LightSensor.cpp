#include "LightSensor.h"
#define ARRAY_SIZE 4

LightSensor::LightSensor(PinName photo0, PinName photo1, PinName photo2, PinName photo3){
    photoArray[0] = new AnalogIn(photo0);
    photoArray[1] = new AnalogIn(photo1);
    photoArray[2] = new AnalogIn(photo2);
    photoArray[3] = new AnalogIn(photo3);
}

float LightSensor::getPhotoValue_f(photoElement element){
    return photoArray[element]->read();
}

unsigned short LightSensor::getPhotoValue_u16(photoElement element){
    return photoArray[element]->read_u16();
}