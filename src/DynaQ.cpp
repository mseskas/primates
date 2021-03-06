#include "DynaQ.h"

// destructor to release memory
DynaQ::~DynaQ(){
    logFile.close();
    StateModel->ReleaseState();
    RedLED->TurnOff();
    GreenLED->TurnOff();
    cout << "DynaQ deleted";
}

DynaQ::DynaQ(IState* allServoModel, IReward* rewardModel)
{
    BETA = 0.9;
    GAMA = 0.5;
    EPSILON = 0.01;
    TotalReward = 0;
    CurrentIteration = 0;
    StateModel = allServoModel;
    RewardModel = rewardModel;
    srvQuantity = allServoModel->srvQuantity;
    GreenLED = new LED(GREEN_LED_PIN);
    RedLED = new LED(RED_LED_PIN);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    dateTimeStr = "dyna ";
    dateTimeStr.append(to_string(ltm->tm_mday) + " ");

    dateTimeStr.append(to_string(ltm->tm_hour) + ":");
    dateTimeStr.append(to_string(ltm->tm_min) + ":");
    dateTimeStr.append(to_string(ltm->tm_sec));

    logFile.open("logs/" + dateTimeStr + ".txt");
    logFile << "beta " << BETA << " gama " << GAMA << " epsilon " << EPSILON << endl;
    logFile << "IterationNo - in beginning of the line, s - state, r - received reward, rs - total reward" << endl;
}

void DynaQ::PrepareToLearn() {
    cout << "Preparing DYNO..." << endl;
    CurrentState  =  StateModel->BeginState();
    logFile << "start state: " << CurrentState << endl;

    for (int s = 0; s < Statequantity; s++){
        for (int a = 0; a < Statequantity; a++){
            Model[s][a] = UnidentifiedRewardSign;
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
    cout << "total reward:\t" << TotalReward << endl;
    logFile << "\tReceived reward:\t" << reward << "\tTotal: \t" << TotalReward;
    cout << "\tReceived reward:\t" << reward << "\tTotal: \t" << TotalReward;
}

void DynaQ::RunIterations(int iterations, bool useMPU, short nextState=-1, short reward=-1){
  //  if (useMPU) {
  //      for (int i = 0; i < iterations; i++) RunIterationMPU( nextState,  reward);
  //  }
 //   else {
        for (int i = 0; i < iterations; i++) RunIteration( nextState,  reward);
  //  }
}

void DynaQ::RunIteration(short forcedNextState = -1, short forcedReward = -1){
        short nextState = EGreedyByQuality(CurrentState);

        if (forcedNextState == -1){
            nextState = EGreedyByQuality(CurrentState);
        } else {
            nextState = forcedNextState;
        }

logFile << CurrentIteration << "\tIn state:\t" << CurrentState << "\tchoose\t" << nextState;
cout << CurrentIteration << "\tIn state:\t" << CurrentState << "\tchoose\t" << nextState;
        RewardModel->StartMeasure();
        StateModel->ExecutePosition(nextState); // asynchronous

// start learn calculations in parallel
        short reward = lastReward;

//        char input;
//        cout << "insert reward 1 - forward, 0 - still, . - backward: ";
//        cin >> input;
//        cout << endl;
//
//        switch (input) {
//            case '1':
//                reward = 100;
//                break;
//            case '0':
//                reward = 0;
//                break;
//            case '.':
//                reward = -100;
//                break;
//        }

        if (forcedReward != -1){
            reward = forcedReward;
        }

        IndicateResult(reward);
        Q[CurrentState][nextState] = (Q[CurrentState][nextState] - BETA * (Q[CurrentState][nextState])) + BETA * (reward  + GAMA * GetMaxQuality(nextState));

        if (Q[CurrentState][nextState]  >= 200)
            for (int i = 0; i < 10; i++)
                cout << "ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR"<< endl;


        //Q(s, a) = Q(s, a) + β(r + γmax a ′ Q(s ′ , a ′ ) − Q(s, a))

logFile << "\tUpdate Q(" << CurrentState << ", " << nextState << ") = " << Q[CurrentState][nextState] << endl;
cout << "\tUpdate Q(" << CurrentState << ", " << nextState << ") = " << Q[CurrentState][nextState] << endl;



        //Update Model
        Model[CurrentState][nextState] = reward;
        // learn from model
        short PlanningCurrentState = CurrentState;
        for (int i = 0; i < PlanningSteps; i++){
            if (PlanningCurrentState != -1) PlanningCurrentState = DoPlanning(PlanningCurrentState);
        }

        CurrentIteration++;
        Exploration[CurrentState][nextState] = CurrentIteration;
// stop learn calculations in parallel


        lastReward = RewardModel->StopMeasure();
        lastState = CurrentState;
        CurrentState = nextState;
}



// return previously occupied state, when update is success, -1 - when nothing to update
short DynaQ::DoPlanning(short currentstate){
    short repeatedValues = -1;
    short previousState = -1;

    for (short i = 0; i < Statequantity; i++){
        // when occurred reward
        if (Model[i][currentstate] != UnidentifiedRewardSign){
            repeatedValues++;
            Temporary[repeatedValues] = i;
        }
    }

    if (repeatedValues == 0) previousState = Temporary[repeatedValues];
    if (repeatedValues > 0){
        int randomState = rand() % repeatedValues + 1;  // rand = [0; repeatedValues]
        previousState = Temporary[randomState];
    }

    // update
    if (previousState == -1) return previousState;

    // epsilon not needed
    float oldValue = Q[previousState][currentstate];
    float reward = Model[previousState][currentstate];

    Q[previousState][currentstate] = oldValue + BETA * (reward + (GAMA * GetMaxQuality(currentstate)) - oldValue);


     if (Q[previousState][currentstate]  >= 200)
            for (int i = 0; i < 10; i++)
                cout << "ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR"<< endl;



    return previousState;
}

// max Q(s,a)
short DynaQ::GetMaxQuality(short state){
    float maxQ = Q[state][0];

     for (short a = 1; a < Statequantity; a++){
        if (Q[state][a] > maxQ) maxQ = Q[state][a];
     }

     return maxQ;
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
            repeatedValues++;
            Temporary[repeatedValues] = a;
        }
    }
    //logFile << "egreedyByQuality repeatedValues - " << repeatedValues << "\t value = " << maxQ << endl;
    cout << "egreedyByQuality repeatedValues - " << repeatedValues << "\t value = " << maxQ << endl;
    if (repeatedValues > 0){
        int randomState = rand() % repeatedValues + 1;  // rand = [0; repeatedValues]
        return Temporary[randomState];
    }
    return maxA;
}

//epsilon-greedy with update on each check: return State number
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



