#ifndef REWARD_H
#define REWARD_H

#include "MPU6050.h"
#include "Sonar.h"
#include <gtk/gtk.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include <mutex>

class Reward
{
    public:
        Reward(MPU6050 * mpuChip, Sonar * sonar);

//        void SetIterationduration(int milliseconds);
//        void SetRewardThreshold(float threshold);
//        void SetSeparateDuration(float milliseconds);

        float IntervalMs; // time between measure
        float Threshold;
        int DurationMs;  // total measure duration

        double SyncGetReward();
        void AsyncGetReward(bool waitToFinish = false);
        void StartMeasure();
        short StopMeasure();

        double LastResult;
        int LastDistance;


        //  Result is set to category where { fail, nothing, success} respectively :
        static const short CategoryResult[3] = { -100, 0, 100 };
        short ResultCategory;

        GtkWidget * OutputLabel;

        bool HasMPU;
        bool HasSONAR;

        int IterationNumber;
        ofstream logFile;

        std::thread * _execution_thread;
        std::mutex ExecutionLock;
        bool IsRunning;

    protected:
    private:
        Sonar * FrontSonar;
        MPU6050 * _mpuChip;
};

#endif // REWARD_H
