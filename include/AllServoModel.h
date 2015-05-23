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
        char* BeginState();

        char LastState[srvQuantity];

        servo * Servos[srvQuantity+1];
        int * ServoParams;

    protected:
    private:

        void LoadServoControls();

};

#endif // ALLSERVOMODEL_H
