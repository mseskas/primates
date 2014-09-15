#ifndef DYNAQ_H
#define DYNAQ_H

#include <iostream>
#include <fstream>
#include <ctime>

#include "RewardView.h"
#include "AllServoModel.h"

using namespace std;

class DynaQ
{
    public:
        DynaQ(AllServoModel * allServoModel, Reward * rewardModel);
        ~DynaQ();
        static const int Squantity =  4096;
        int srvQuantity;

        char * CurrentState;



        void BeginState();

        float Q[Squantity][Squantity];
        char R[Squantity][Squantity];

        float BETA;
        float GAMA;
        float EPSILON;

        AllServoModel * StateModel;
        Reward * RewardModel;
    protected:
    private:

        ofstream file;
        string dateTimeStr;
};

#endif // DYNAQ_H
