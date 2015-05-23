#include "DynaQ.h"

// destructor to release memory
DynaQ::~DynaQ(){
    logFile.close();
    cout << "DynaQ deleted";
}

DynaQ::DynaQ(AllServoModel * allServoModel, Reward * rewardModel)
{
    float BETA = 0.9;
    float GAMA = 0.9;
    float EPSILON = 0.01;
    TotalReward = 0;
    Iteration = 0;
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

    logFile.open("logs/" + dateTimeStr + ".txt");
    logFile << "IterationNo - in beginning of the line, s - state, r - received reward, rs - total reward" << endl;

    PrepareToLearn();
}

void DynaQ::PrepareToLearn() {
    cout << "Preparing Primates..." << endl;
    CurrentState  =  StateModel->BeginState();
    logFile << "s " << CurrentState << endl;

    for (int s = 0; s < Statequantity; s++){
        for (int a = 0; a < Statequantity; a++){
            Model[s][a] = 0;
            Q[s][a] = 0;
            Exploration[s][a] = 0;
        }
    }
    cout << "Model and Quality is set to zero" << endl;
}




















