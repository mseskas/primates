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

        void ExecutePosition(const char * data12);
        void ExecutePosition(short state);

        short BeginState();

      //  char LastState[srvQuantity+1];
        short LastState;

        servo * Servos[srvQuantity];
        int * ServoParams;



    protected:
    private:

        void LoadServoControls();

};

#endif // ALLSERVOMODEL_H
