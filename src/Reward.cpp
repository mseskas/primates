#include "Reward.h"


Reward::Reward(MPU6050 * mpuChip) {
    HasMPU = false;
    _mpuChip = mpuChip;
    if (mpuChip != NULL) HasMPU = true;
    DurationMs = 2500; // milliseconds
    IntervalMs = 30;
    Threshold = 0.05;
    IsRunning = false;
}

bool Reward::AsyncGetReward(){
    if (IsRunning == true) return false;

    _execution_thread = new std::thread (&Reward::GetReward, this);
    return true;
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
            cout << "[" << minAX << ":" << maxAX << "]\t";
            cout << "[" << minIteration << ":" << maxIteration << "]\t" << measure << endl;
            delay(IntervalMs);
            iteration++;
        }

        if (minIteration == 2000000 && maxIteration == 2000000) {
            LastResult = 0;
            cout << "standing still" << endl;
        }
        else {
            if (minIteration < maxIteration){
                // min WIN - forward
                cout << "FORWARD!" << minAX << endl;
                LastResult = minAX;
            }
            // max WIN - backward
            cout << "BACKWARD!" << maxAX << endl;
            LastResult = maxAX;
        }
    } else{
        delay(DurationMs);
        LastResult = 0;
    }


    string output = to_string(LastResult);
    if (LastResult > 0)output.append(" - BACKWARD");
    else output.append(" - FORWARD");
    gtk_label_set_text((GtkLabel*)OutputLabel, output.c_str() );

    IsRunning = false;
    return LastResult;
}
