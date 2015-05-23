#ifndef REWARD_H
#define REWARD_H

#include "MPU6050.h"
#include <gtk/gtk.h>
#include <thread>
#include <cstdlib>

#include <mutex>

class Reward
{
    public:
        Reward(MPU6050 * mpuChip);

//        void SetIterationduration(int milliseconds);
//        void SetRewardThreshold(float threshold);
//        void SetSeparateDuration(float milliseconds);

        float IntervalMs; // time between measure
        float Threshold;
        int DurationMs;  // total measure duration

        double GetReward();
        void AsyncGetReward(bool waitToFinish = false);

        double LastResult;
        short ResultCategory;

        GtkWidget * OutputLabel;

        bool HasMPU;

        std::thread * _execution_thread;
        std::mutex ExecutionLock;
        bool IsRunning;

    protected:
    private:

        MPU6050 * _mpuChip;
};

#endif // REWARD_H
