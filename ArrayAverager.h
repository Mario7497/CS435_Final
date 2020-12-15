
#ifndef ARRAYAVERAGER_H
#define ARRAYAVERAGER_H
#define NUM_RES 4
#define TIME_QUANTUM 4


class ArrayAverager{
    private:
        unsigned short timeIndex = 0;
        float array[NUM_RES][TIME_QUANTUM];
        float avgArray[NUM_RES];
    public:
        ArrayAverager(int x);
        float *updateArray(float newData[]);
};


#endif