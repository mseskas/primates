#ifndef IREWARD_H
#define IREWARD_H


class IReward
{
    public:
        virtual void StartMeasure() = 0;
        virtual short StopMeasure() = 0;
        virtual double SyncGetReward() = 0;
        virtual void AsyncGetReward(bool waitToFinish = false) = 0;
        short ResultCategory;
};

#endif // IREWARD_H
