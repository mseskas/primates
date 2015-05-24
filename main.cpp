#include <iostream>
#include <string>
#include "gui_main.h"
#include "Reward.h"
#include "DynaQ.h"

#include <signal.h>

#include "AllServoModel.h"

using namespace std;

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

    AllServoModel * servosModel = new AllServoModel();
    Reward * reward = new Reward(new MPU6050());
    gui_main * main_gui = new gui_main(servosModel, reward);
    dyna = new DynaQ(servosModel, reward);

    char str[80];

    char c;

    bool execute = true;
    while (execute) {
        cout << "Enter command: " <<  endl;
        cin >> c;

        //scanf ("%79s",&str);

        switch (c){
            case '1':
                dyna->RunIterations(1);
                break;
            case '0':
                dyna->PrepareToLearn();
                break;
            case '5':
                dyna->RunIterations(2);
                break;
            case '6':
                dyna->RunIterations(4);
                break;
            case '7':
                dyna->RunIterations(8);
                break;
            case '8':
                dyna->RunIterations(16);
                break;
            case '9':
                dyna->RunIterations(64);
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
