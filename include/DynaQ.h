#ifndef DYNAQ_H
#define DYNAQ_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <thread>   // std::sleep_for
#include <chrono>   // std::chrono::seconds
#include <sys/stat.h> // mkdir

#include "RewardView.h"
#include "AllServoModel.h"
#include "LED.h"


using namespace std;

class DynaQ
{
    public:
        DynaQ(AllServoModel * allServoModel, Reward * rewardModel);
        ~DynaQ();
        static const short Statequantity =  256;
        //static const short Statequantity =  4096;
        static const int PlanningSteps = 10;
        static const char UnidentifiedRewardSign = -88;
        int srvQuantity;

        double TotalReward;
        short CurrentState;
        short CurrentIteration;


        void PrepareToLearn();
        short DoPlanning(short currentstate);
        short EGreedy(short currentState);
        short EGreedyByQuality(short currentState);
        short GetMaxQuality(short state);

        void RunIterations(int iterations, bool useMPU);

        void RunIterationMPU();
        void RunIterationSONAR();

        void IndicateResult(short reward);
        //float MaxQ[Statequantity];

        /// [state from][state to]
        float Q[Statequantity][Statequantity];
        char Model[Statequantity][Statequantity];
        short Exploration[Statequantity][Statequantity];  // last iteration number
        short Temporary[Statequantity];

        float BETA;  // 0.9
        float GAMA;  // 0.9
        float EPSILON; // 0.01
        AllServoModel * StateModel;
        Reward * RewardModel;
        LED * GreenLED;
        LED * RedLED;

    protected:
    private:



        ofstream logFile;
        string dateTimeStr;
};

#endif // DYNAQ_H
