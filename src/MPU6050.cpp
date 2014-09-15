#include "MPU6050.h"

MPU6050::MPU6050() {
    _WAKEUP = 0x6b;
    _RTEMP = 0x41;
    _RACCELX = 0x3b;
    _RACCELY = 0x3d;
    _RACCELZ = 0x3f;
    _RGYROX = 0x43;
    _RGYROY = 0x45;
    _RGYROZ = 0x47;

   wiringPiSetup ();
   _chipHandler = wiringPiI2CSetup(MPU6050_ADDR);
   cout << "MPU handler: " << _chipHandler << endl;
   WakeUp();
}

void MPU6050::WakeUp() {
    wiringPiI2CWriteReg8(_chipHandler, _WAKEUP, 0x00);
    delay(100);
}

double MPU6050::GetXRotation(double accelX, double accelY, double accelZ) {
    double radians = atan2 (accelY, Distance(accelX, accelZ));
    return -radians * 180 / PI;
}

double MPU6050::GetYRotation(double accelX, double accelY, double accelZ) {
    double radians = atan2 (accelX, Distance(accelY, accelZ));
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
    float value = (float)ReadValue(_RACCELX);
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
