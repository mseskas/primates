#ifndef REWARD_H
#define REWARD_H

#include "MPU6050.h"

class Reward
{
    public:
        Reward(MPU6050 * mpuChip);

        void SetIterationduration(int milliseconds);
        void SetRewardThreshold(float threshold);
        void SetSeparateDuration(float milliseconds);


        double GetReward();

    protected:
    private:
        float _separationDurationMs; // time between measure
        float _threshold;
        int _durationMs;  // total measure duration
        MPU6050 * _mpuChip;
};

#endif // REWARD_H
