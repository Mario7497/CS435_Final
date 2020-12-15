#include "ArrayAverager.h"


ArrayAverager::ArrayAverager(int x){
  for (int resistor = 0; resistor < NUM_RES; resistor++) {
    for (int time = 0; time < TIME_QUANTUM; time++) {
      array[resistor][time] = 0.0;
    }
  }
}

float* ArrayAverager::updateArray(float newData[]){
    for (int resistor = 0; resistor < NUM_RES; resistor++) {
        array[resistor][timeIndex] = newData[resistor];
    }
    timeIndex = (timeIndex + 1) % TIME_QUANTUM;
    
    float tmp = 0.0;
    
    for (int resistor = 0; resistor < NUM_RES; resistor++) {
        for (int time = 0; time < TIME_QUANTUM; time++) {
            tmp += array[resistor][time];
        }
        tmp /= TIME_QUANTUM;
        avgArray[resistor] = tmp;
        tmp = 0.0;
    }
    return avgArray;
}