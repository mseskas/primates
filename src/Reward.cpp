#include "Reward.h"


Reward::Reward(MPU6050 * mpuChip) {
    _mpuChip = mpuChip;
    DurationMs = 2500; // milliseconds
    IntervalMs = 30;
    Threshold = 0.05;
}

double Reward::GetReward(){
    int iteration = 0;
    int minIteration;
    int maxIteration;
    minIteration = maxIteration = 2000000;

    double minAX = 0;
    double maxAX = 0;

    double leanAX;

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

    if (minIteration == 2000000 && maxIteration == 2000000) return 0;

    if (minIteration < maxIteration){
        // min WIN - forward
        cout << "FORWARD!" << minAX << endl;
        return minAX;
    }
    // max WIN - backward
    cout << "BACKWARD!" << maxAX << endl;
    return maxAX;
}
