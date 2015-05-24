#include "DynaQ.h"

// destructor to release memory
DynaQ::~DynaQ(){
    logFile.close();
    StateModel->ReleaseMotors();
    RedLED->TurnOff();
    GreenLED->TurnOff();
    cout << "DynaQ deleted";
}

DynaQ::DynaQ(AllServoModel * allServoModel, Reward * rewardModel, Sonar * frontSonar)
{
    BETA = 0.9;
    GAMA = 0.5;
    EPSILON = 0.1;
    TotalReward = 0;
    CurrentIteration = 0;
    StateModel = allServoModel;
    RewardModel = rewardModel;
    srvQuantity = allServoModel->srvQuantity;
    GreenLED = new LED(GREEN_LED_PIN);
    RedLED = new LED(RED_LED_PIN);
    FrontSonar = frontSonar;

    time_t now = time(0);
    tm *ltm = localtime(&now);

    dateTimeStr = "dyna ";
    dateTimeStr.append(to_string(ltm->tm_mday) + " ");

    dateTimeStr.append(to_string(ltm->tm_hour) + ":");
    dateTimeStr.append(to_string(ltm->tm_min) + ":");
    dateTimeStr.append(to_string(ltm->tm_sec));

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
}


void DynaQ::IndicateResult(short reward){
    if (reward == 100) {
        GreenLED->TurnON();
        RedLED->TurnOff();
    } else {
        GreenLED->TurnOff();
        RedLED->TurnON();
    }
    TotalReward += reward;
    logFile << "Received reward: " << reward << "\tTotal: " << TotalReward << endl;
}

void DynaQ::RunIterations(int iterationsNo){

    for (int i = 0; i < iterationsNo; i++){
        //short nextState = EGreedy(CurrentState);
        short nextState = EGreedyByQuality(CurrentState);
logFile << "In state: " << CurrentState << " choose " << nextState << endl;

        RewardModel->AsyncGetReward();
        delay(120);
        StateModel->ExecutePosition(nextState);
        RewardModel->AsyncGetReward(true); // just waiting to finish measurement
        short reward = RewardModel->ResultCategory;
        IndicateResult(reward);

        Q[CurrentState][nextState] = Q[CurrentState][nextState] + BETA * (reward
        // always = 0  //+ EPSILON * sqrt(CurrentIteration - Exploration[CurrentState][nextState])
            + GAMA * GetMaxQuality(nextState) - Q[CurrentState][nextState]); //old:
        //Q(s, a) = Q(s, a) + β(r + γmax a ′ Q(s ′ , a ′ ) − Q(s, a))

// if (Q[CurrentState][nextState] > MaxQ[CurrentState]) MaxQ[CurrentState] = Q[CurrentState][nextState];

logFile << "Update Q(" << CurrentState << ", " << nextState << ") = " << Q[CurrentState][nextState] << endl << endl;

        //Update Model
        Model[CurrentState][nextState] = reward;

        CurrentIteration++;
        Exploration[CurrentState][nextState] = CurrentIteration;
        CurrentState = nextState;
        delay(00);
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
short DynaQ::EGreedy(short state){
    float maxQ=0;
    short maxA=0;
    short repeatedValues = 0;

    maxQ = Model[state][maxA] + (EPSILON * sqrt(CurrentIteration - Exploration[state][maxA]))
        + GAMA * (GetMaxQuality(maxA)); // arbitrary action
    Temporary[repeatedValues] = maxA;

    for (short a = 1; a < Statequantity; a++){
        if (state == a) continue; // skip current state
        float currentQ = Model[state][a] + (EPSILON * sqrt(CurrentIteration - Exploration[state][a]))
            + GAMA * (GetMaxQuality(a));

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

//epsilon-greedy: return State number
short DynaQ::EGreedyByQuality(short state){
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


















