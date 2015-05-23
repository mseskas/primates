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
        static const short Statequantity =  4096;
        int srvQuantity;

        char * CurrentState;



        void PrepareToLearn();



        /// [state from][state to]
        float Q[Statequantity][Statequantity];
        char Model[Statequantity][Statequantity];
        short Exploration[Statequantity][Statequantity];

        float BETA;  // 0.9
        float GAMA;  // 0.9
        float EPSILON; // 0.01

        double TotalReward;
        short Iteration;

        AllServoModel * StateModel;
        Reward * RewardModel;
    protected:
    private:

        ofstream logFile;
        string dateTimeStr;
};

#endif // DYNAQ_H
