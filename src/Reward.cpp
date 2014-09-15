#include "Reward.h"


Reward::Reward(MPU6050 * mpuChip) {
    _mpuChip = mpuChip;
    _durationMs = 2500; // milliseconds
    _separationDurationMs = 30;
    _threshold = 0.05;
}

void Reward::SetIterationduration(int milliseconds) {
    _durationMs = milliseconds;
}

void Reward::SetRewardThreshold(float threshold) {
    _threshold = threshold;

}

void Reward::SetSeparateDuration(float milliseconds){
    _separationDurationMs = milliseconds;
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

    for (int i = 0; i < _durationMs; i += _separationDurationMs){

        double measure = _mpuChip->GetAccelX() - leanAX;
        if (measure > 0.05 || measure < -0.05){
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
        delay(_separationDurationMs);
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
