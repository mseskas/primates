#include "MPU6050.h"

MPU6050::MPU6050(int chipAddr) {
    _WAKEUP = 0x6b;
    _RTEMP = 41;
    _RACCELX = 43;
    _RACCELY = 45;
    _RACCELZ = 47;
    _RGYROX = 0x3b;
    _RGYROY = 0x3d;
    _RGYROZ = 0x3f;

    wiringPiSetup ();
    _chipHandler = wiringPiI2CSetup(chipAddr) ;
    WakeUp();
}

void MPU6050::WakeUp() {
    wiringPiI2CWriteReg8(_chipHandler, _WAKEUP, 0x00);
    delay(0.1);
}

double MPU6050::GetXRotation(double accelX, double accelY, double accelZ) {
    double radians = atan2 (y, Distance(x, z));
    return -radians * 180 / PI;
}

double MPU6050::GetYRotation(double accelX, double accelY, double accelZ) {
    double radians = atan2 (x, Distance(y, z));
    return -radians * 180 / PI;
}

double MPU6050::Distance(double a, double b) {
     return sqrt((a*a)+(b*b));
}

int MPU6050::ReadValue(int address){
    int high = wiringPiI2CReadReg8(_chipHandler, address);
    int low = wiringPiI2CReadReg8(_chipHandler, address+1);

    int value = (high << 8) + low;

    if (value >= 0x8000)
        return -((65535 - value) + 1);
    else
        return value;
}

double MPU6050::GetAccelX(){
    float value = (float)ReadValue(_RACCELZ);
    return value / 16384.0;
}

double MPU6050::GetAccelY() {
    float value = (float)ReadValue(_RACCELY);
    return value / 16384.0;
}

double MPU6050::GetAccelZ() {
    float value = (float)ReadValue(_RACCELZ);
    return value / 16384.0;
}

double MPU6050::GetGyroX() {
    float value = (float)ReadValue(_RGYROX);
    return value / 131;
}

double MPU6050::GetGyroY() {
    float value = (float)ReadValue(_RGYROY);
    return value / 131;
}

double MPU6050::GetGyroZ() {
    float value = (float)ReadValue(_RGYROZ);
    return value / 131;
}
