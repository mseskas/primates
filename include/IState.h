#ifndef ISTATE_H
#define ISTATE_H


class IState
{
    public:
        virtual void ExecutePosition(const char * data12) = 0;
        virtual void ExecutePosition(short state) = 0;
        virtual short BeginState() = 0;
        virtual void ReleaseState() = 0;
        short LastState;
        int srvQuantity;
};

#endif // ISTATE_H
