#ifndef MPU6050_H
#define MPU6050_H

#include <stdlib.h>
#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <project_constants.h>
#include <math.h> // math functions, like sqrt, pow...

using namespace std;

class MPU6050
{
    public:
        MPU6050();

        double GetXRotation(double accelX, double accelY, double accelZ);
        double GetYRotation(double accelX, double accelY, double accelZ);

        double GetAccelX();
        double GetAccelY();
        double GetAccelZ();

        double GetGyroX();
        double GetGyroY();
        double GetGyroZ();

        void WakeUp();

    protected:
    private:
        double Distance(double a, double b);
        int _chipHandler;
        int _WAKEUP;
        int _RTEMP;
        int _RACCELX;
        int _RACCELY;
        int _RACCELZ;
        int _RGYROX;
        int _RGYROY;
        int _RGYROZ;

        int ReadValue(int address);
};

#endif // MPU6050_H
