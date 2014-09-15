#include "DynaQ.h"

// destructor to release memory
DynaQ::~DynaQ(){
    file.close();
//                            delete pointer;
//                            delete[] pointer;
}

DynaQ::DynaQ(AllServoModel * allServoModel, Reward * rewardModel)
{
    float BETA = 0.9;
    float GAMA = 0.9;
    float EPSILON = 0.01;
    StateModel = allServoModel;
    RewardModel = rewardModel;
    srvQuantity = allServoModel->srvQuantity;

    time_t now = time(0);
    tm *ltm = localtime(&now);

    dateTimeStr = to_string(1900 + ltm->tm_year) + "-";
    dateTimeStr.append(to_string(1 + ltm->tm_mon) + "-");
    dateTimeStr.append(to_string(ltm->tm_mday) + " ");

    dateTimeStr.append(to_string(ltm->tm_hour) + ":");
    dateTimeStr.append(to_string(ltm->tm_min) + ":");
    dateTimeStr.append(to_string(ltm->tm_sec));

    file.open("logs/" + dateTimeStr + ".txt");

    BeginState();
}

void DynaQ::BeginState() {
    CurrentState  =  StateModel->BeginState();


//StateModel->

}
















