#ifndef ALLSERVOMODEL_H
#define ALLSERVOMODEL_H

#include <PwmChip.h>
#include "Servo.h"
#include <iostream>
#include <cstring>
#include "IState.h"


using namespace std;

class ServoModel : public IState
{
    public:
        static const int srvQuantity = 12;
        ServoModel();

        void ExecutePosition(const char * data12);
        void ExecutePosition(short state);

        void SetSinglePosition(int servo, float anglePercent);
        void SetAllPositions(float * positions);

        void ReleaseState();

        short BeginState();

      //  char LastState[srvQuantity+1];
        short LastState;

        servo * Servos[srvQuantity];
        int * ServoParams;

        float * ServoPositions;

    private:
        void LoadServoControls();

};

#endif // ALLSERVOMODEL_H
