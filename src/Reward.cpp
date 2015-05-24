#include "Reward.h"


Reward::Reward(MPU6050 * mpuChip) {
    HasMPU = false;
    _mpuChip = mpuChip;
    if (mpuChip != NULL) HasMPU = true;
    DurationMs = 1500; // milliseconds
    IntervalMs = 20;
    Threshold = 0.3;
    IsRunning = false;
    OutputLabel = NULL;
    ResultCategory = 0;
    IterationNumber = 1;
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

void Reward::AsyncGetReward(bool waitToFinish = false){
    ExecutionLock.lock();

    if (waitToFinish) ExecutionLock.unlock(); // just leave, this means LastResult is initialized
    else _execution_thread = new std::thread (&Reward::GetReward, this);
}


double Reward::GetReward(){
    IsRunning = true;
    int iteration = 0;
    int minIteration;
    int maxIteration;
    minIteration = maxIteration = 2000000;
    double minAX = 0;
    double maxAX = 0;
    double leanAX;

    if (HasMPU){
        leanAX = _mpuChip->GetAccelX(); // initialization

        for (int i = 0; i < DurationMs; i += IntervalMs){
            double measure = _mpuChip->GetAccelX() - leanAX;
            if (measure > Threshold || measure < -Threshold){
                if (measure < minAX){
                    minAX = measure;
                    minIteration = iteration;
                }
                else if (measure > maxAX){
                    maxAX = measure;
                    maxIteration = iteration;
                }
            }
            logFile << IterationNumber << "\t" << measure << " [" << minAX << ":" << maxAX << "]\t";
            logFile << "[" << minIteration << ":" << maxIteration << "]" << endl;

            cout << "[" << minAX << ":" << maxAX << "]\t";
            cout << "[" << minIteration << ":" << maxIteration << "]\t" << measure << endl;
            delay(IntervalMs);
            iteration++;
        }
        logFile << "result : ";
        if (minIteration == 2000000 && maxIteration == 2000000) {
            LastResult = 0;
            ResultCategory = -10;
            logFile << "Standing:|" << endl;
            cout << "standing still:|" << endl;
        }
        else {
            if (minIteration < maxIteration){
                // min WIN - forward
                logFile << "FORWARD:)" << endl;
                cout << "FORWARD:)" << minAX << endl;
                ResultCategory = 100;
                LastResult = minAX;
            }
            else {// max WIN - backward
                logFile << "BACKWARD:(" << endl;
                cout << "BACKWARD:(" << maxAX << endl;
                ResultCategory = -100;
                LastResult = maxAX;
            }
        }
        logFile << endl;
        IterationNumber++;
    } else{
        delay(DurationMs);
        ResultCategory = 0;
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
