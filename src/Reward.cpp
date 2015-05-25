#include "Reward.h"



Reward::Reward(MPU6050 * mpuChip, Sonar * sonar)
{
    HasMPU = false;
    HasSONAR = false;
    CategoryResult[0] = -100;
    CategoryResult[1] = 0;
    CategoryResult[2] = 100;

    _mpuChip = mpuChip;
    FrontSonar = sonar;
    if (mpuChip != NULL) HasMPU = true;
    if (sonar != NULL) HasSONAR = true;
    DurationMs = 1500; // milliseconds
    IntervalMs = 20;
    Threshold = 0.3;
    IsRunning = false;
    OutputLabel = NULL;
    ResultCategory = 0;
    IterationNumber = 1;
    GreenLED = new LED(GREEN_LED_PIN);
    RedLED = new LED(RED_LED_PIN);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    string dateTimeStr = "reward ";
    dateTimeStr.append(to_string(ltm->tm_mday) + " ");

    dateTimeStr.append(to_string(ltm->tm_hour) + ":");
    dateTimeStr.append(to_string(ltm->tm_min) + ":");
    dateTimeStr.append(to_string(ltm->tm_sec));

    logFile.open("logs/" + dateTimeStr + ".txt");
    logFile << "#syntax: iterationNumber, AccelX, minX, maxX, minIteration, maxIteration" << endl;
}

void Reward::AsyncGetReward(bool waitToFinish = false)
{
    ExecutionLock.lock();

    if (waitToFinish) ExecutionLock.unlock(); // just leave, this means LastResult is initialized
    else _execution_thread = new std::thread (&Reward::SyncGetReward, this);
}

double Reward::SyncGetReward()
{
    IsRunning = true;
    int iteration = 0;
    int minIteration;
    int maxIteration;
    minIteration = maxIteration = 2000000;
    double minAX = 0;
    double maxAX = 0;
    double leanAX;

    if (HasMPU)
    {
        leanAX = _mpuChip->GetAccelX(); // initialization

        for (int i = 0; i < DurationMs; i += IntervalMs)
        {
            double measure = _mpuChip->GetAccelX() - leanAX;
            if (measure > Threshold || measure < -Threshold)
            {
                if (measure < minAX)
                {
                    minAX = measure;
                    minIteration = iteration;
                }
                else if (measure > maxAX)
                {
                    maxAX = measure;
                    maxIteration = iteration;
                }
            }
            logFile << IterationNumber << "\t" << measure << "\t[" << minAX << ":" << maxAX << "]\t";
            logFile << "[" << minIteration << ":" << maxIteration << "]" << endl;

           // cout << "[" << minAX << ":" << maxAX << "]\t";
            //cout << "[" << minIteration << ":" << maxIteration << "]\t" << measure << endl;
            delay(IntervalMs);
            iteration++;
        }
        logFile << "result : ";
        if (minIteration == 2000000 && maxIteration == 2000000)
        {
            LastResult = 0;
            ResultCategory = CategoryResult[1];
            logFile << "Standing:|" << endl;
            cout << "Standing still:|" << endl;
        }
        else
        {
            if (minIteration < maxIteration)
            {
                // min WIN - forward
                logFile << "FORWARD:)" << endl;
                cout << "FORWARD:)" << minAX << endl;
                ResultCategory = CategoryResult[2];
                LastResult = minAX;
            }
            else  // max WIN - backward
            {
                logFile << "BACKWARD:(" << endl;
                cout << "BACKWARD:(" << maxAX << endl;
                ResultCategory = CategoryResult[0];
                LastResult = maxAX;
            }
        }
        logFile << endl;
        IterationNumber++;
    }
    else
    {
        delay(DurationMs);
        ResultCategory = CategoryResult[1];
        LastResult = 0;
    }

    if (OutputLabel != NULL)
    {
        string output = to_string(LastResult);
        if (LastResult > 0)output.append(" - BACKWARD");
        else output.append(" - FORWARD");
        gtk_label_set_text((GtkLabel*)OutputLabel, output.c_str() );
    }
    IsRunning = false;
    ExecutionLock.unlock();
    return LastResult;
}

void Reward::StartMeasure()
{
    ResultCategory = 0;
    if (!HasSONAR) return false;

    LastDistance = FrontSonar->GetFilteredDistance();

    if (LastDistance < 8){
        InicatePause();
        LastDistance = FrontSonar->GetFilteredDistance();
    }

    logFile << "Start measure: \t" << LastDistance << endl;
    cout << "Start measure: \t" << LastDistance << endl;
}

void Reward::InicatePause(){
    GreenLED->TurnON();
    RedLED->TurnON();
    cout << "PAUSE STATE!!!!!" << endl;
    while (FrontSonar->GetFilteredDistance() < 8){
        GreenLED->TurnOff();
        RedLED->TurnOff();
        delay(333);
        GreenLED->TurnON();
        RedLED->TurnON();
    }
}

short Reward::StopMeasure()
{
    if (!HasSONAR)
    {
        ResultCategory = CategoryResult[1];
        return ResultCategory;
    }

    int distance = FrontSonar->GetFilteredDistance();

    logFile << "Stop measure: \t" << distance;
    cout << "Stop measure: \t" << distance;



    // standing still: -1, 0, +1
    if (-2 < (distance - LastDistance) && (distance - LastDistance) < 2) {
        ResultCategory = CategoryResult[1];
        logFile << "\tResult: Standing Still" << endl;
        cout << "\tResult: Standing Still" << endl;
    }

    else {
        // forward
        if (distance < LastDistance) {
            ResultCategory = CategoryResult[2];
            logFile << "\tResult: FORWARD" << endl;
            cout << "\tResult: FORWARD" << endl;
        }
        else  {
            ResultCategory = CategoryResult[0]; // backward
            logFile << "\tResult: BACKWARD" << endl;
            cout << "\tResult: BACKWARD" << endl;
        }
    }

    LastDistance = distance;
    return ResultCategory;
}















