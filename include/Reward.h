#ifndef REWARD_H
#define REWARD_H

#include "MPU6050.h"

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

    protected:
    private:

        MPU6050 * _mpuChip;
};

#endif // REWARD_H
