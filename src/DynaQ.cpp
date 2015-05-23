#include "DynaQ.h"

// destructor to release memory
DynaQ::~DynaQ(){
    logFile.close();
    cout << "DynaQ deleted";
}

DynaQ::DynaQ(AllServoModel * allServoModel, Reward * rewardModel)
{
    BETA = 0.9;
    GAMA = 0.9;
    EPSILON = 0.01;
    TotalReward = 0;
    CurrentIteration = 0;
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

    const int dir_err = mkdir("logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (-1 == dir_err) cout << "Error creating directory!" << endl;

    logFile.open("logs/" + dateTimeStr + ".txt");
    logFile << "IterationNo - in beginning of the line, s - state, r - received reward, rs - total reward" << endl;
}

void DynaQ::PrepareToLearn() {
    cout << "Preparing UOSIS..." << endl;
    CurrentState  =  StateModel->BeginState();
    logFile << "start state: " << CurrentState << endl;

    for (int s = 0; s < Statequantity; s++){
        for (int a = 0; a < Statequantity; a++){
            Model[s][a] = 0;
            Q[s][a] = 0;
            Exploration[s][a] = 0;
        }
    }
    cout << "Model and Quality is set to zero" << endl;

    //GetActionByEgreedy(CurrentState);
}

void DynaQ::RunIterations(int iterationsNo){

    for (int i = 0; i < iterationsNo; i++){

        short nextState = GetActionByEgreedy(CurrentState);

logFile << "In state: " << CurrentState << " choose " << nextState << endl;

        RewardModel->AsyncGetReward();
        delay(120);
        StateModel->ExecutePosition(nextState);
        RewardModel->AsyncGetReward(true); // just waiting to finish measurement
        short reward = RewardModel->ResultCategory;
        TotalReward += reward;
logFile << "Received reward: " << reward << "\tTotal: " << TotalReward << endl;

        Q[CurrentState][nextState] = Q[CurrentState][nextState] + BETA * (reward
        // always = 0  //+ EPSILON * sqrt(CurrentIteration - Exploration[CurrentState][nextState])
            + GAMA * GetMaxQuality(nextState) - Q[CurrentState][nextState]);
        //Q(s, a) = Q(s, a) + β(r + γmax a ′ Q(s ′ , a ′ ) − Q(s, a))

logFile << "Update Q(" << CurrentState << ", " << nextState << ") = " << Q[CurrentState][nextState] << endl << endl;

        //Update Model
        Model[CurrentState][nextState] = reward;

        CurrentIteration++;
        Exploration[CurrentState][nextState] = CurrentIteration;
        CurrentState = nextState;
        delay(1000);
    }
}

// max Q(s,a)
short DynaQ::GetMaxQuality(short state){
    float maxQ = Q[state][0];

     for (short a = 1; a < Statequantity; a++){
        if (Q[state][a] > maxQ){
            maxQ = Q[state][a];
        }
     }
     return maxQ;
}

//epsilon-greedy: return State number
short DynaQ::GetActionByEgreedy(short state){
    float maxQ=0;
    short maxA=0;
    short repeatedValues = 0;

    maxQ = Q[state][maxA] + (EPSILON * sqrt(CurrentIteration - Exploration[state][maxA])); // arbitrary action
    Temporary[repeatedValues] = maxA;

    for (short a = 1; a < Statequantity; a++){
        if (state == a) continue; // skip current state
        float currentQ = Q[state][a] + (EPSILON * sqrt(CurrentIteration - Exploration[state][a]));

        if (currentQ > maxQ){
            repeatedValues = 0;
            Temporary[repeatedValues] = a;
            maxQ = currentQ;
            maxA = a;
        } else if (currentQ == maxQ){
            Temporary[repeatedValues] = a;
            repeatedValues++;
        }

    }

    if (repeatedValues > 0){
        int randomState = rand() % repeatedValues + 1;  // rand = [0; repeatedValues]
        return Temporary[randomState];
    }

    return maxA;
}



















