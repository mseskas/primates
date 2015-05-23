#ifndef ALLSERVOMODEL_H
#define ALLSERVOMODEL_H

#include <pwm_chip.h>
#include "servo.h"
#include <iostream>
#include <cstring>

using namespace std;

class AllServoModel
{
    public:
        static const int srvQuantity = 12;
        AllServoModel();

        int ExecutePosition(char * data12);
        int ExecutePosition(short state);

        char* BeginState();

        char LastState[srvQuantity+1];

        servo * Servos[srvQuantity];
        int * ServoParams;

    protected:
    private:

        void LoadServoControls();

};

#endif // ALLSERVOMODEL_H
