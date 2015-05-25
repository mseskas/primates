#include <iostream>
#include <string>
#include "gui_main.h"
#include "Reward.h"
#include "DynaQ.h"
#include <signal.h>
#include "AllServoModel.h"
#include "Sonar.h"


// TODO: remove if necessary
bool isRaspberryPi = false;

DynaQ * dyna;

void signal_call(int signum){
    printf("Killing Process...");
    dyna->~DynaQ();
    exit(signum);
}

int main()
{
    signal(SIGINT, signal_call);

    const int dir_err = mkdir("logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    struct utsname sysinfo;
    uname(&sysinfo);
    //cout << "Your computer is : " << sysinfo.nodename << endl;
    std::string g = "raspberrypi";
    if ( g.compare(sysinfo.nodename) == 0) isRaspberryPi = true;  // if raspberry


    Sonar* frontSonar = new Sonar(FRONT_SONAR_TRIGGER_PIN, FRONT_SONAR_ECHO_PIN);
    AllServoModel* servosModel = new AllServoModel();

    Reward* reward = new Reward(new MPU6050(), frontSonar);
   // gui_main* main_gui = new gui_main(servosModel, reward);

    dyna = new DynaQ(servosModel, reward);

    char c;

    bool useMPU = false;
    bool execute = true;
    while (execute) {
        cout << "Enter command: " <<  endl;
        cin >> c;

        //scanf ("%79s",&str);

        switch (c){
            case '0':
                dyna->PrepareToLearn();
                break;
            case '1':
                dyna->RunIterations(1, useMPU);
                break;
            case '2':
                dyna->RunIterations(2, useMPU);
                break;
            case '3':
                dyna->RunIterations(4, useMPU);
                break;
            case '4':
                dyna->RunIterations(8, useMPU);
                break;
            case '5':
                dyna->RunIterations(16, useMPU);
                break;
            case '6':
                dyna->RunIterations(6000, useMPU);
                break;
            case 's':
                cout << "measure distance" << endl;
                for (int i = 0; i < 10; i ++) {
                    frontSonar->GetDistance();
                    delay(200);
                }
                break;
            case 'c':
                useMPU = !useMPU;
                cout << "using reward device: " << (useMPU? "MPU": "SONAR") << endl;
                break;
            case 'f':
                short nextState;
                short reward;
                cout << "insert new state ";
                cin >> nextState;
                cout << "insert reward ";
                cin >> reward;
                dyna->RunIterations(1, useMPU, nextState, reward);
                break;
            case 't':
                execute = false;
                break;
        }
    }
//  cout << sizeof(float) << endl;

   //MPU6050 * chip = new MPU6050();
   // Reward * reward = new Reward(chip);

//    cout << "starting..." << endl;
//while (true){
//  //  double rew = reward->GetReward();
//    int t;
//    cin >> t;
//}
   /* for (int i = 0; i < 100000; i++)
    {
        cout << chip->GetAccelX() << "\t" << chip->GetAccelY() << "\t" << chip->GetAccelZ()<< endl;
        delay(100);
    }*/

    delete dyna;

    return 0;
}
