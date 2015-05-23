#include <iostream>
#include <string>
#include "gui_main.h"
#include "Reward.h"
#include "DynaQ.h"


#include "AllServoModel.h"

using namespace std;

// TODO: remove if necessary
bool isRaspberryPi = false;

int main()
{
    struct utsname sysinfo;
    uname(&sysinfo);
    //cout << "Your computer is : " << sysinfo.nodename << endl;
    std::string g = "raspberrypi";
    if ( g.compare(sysinfo.nodename) == 0) isRaspberryPi = true;  // if raspberry

    AllServoModel * servosModel = new AllServoModel();
    Reward * reward = new Reward(new MPU6050());

    gui_main * main_gui = new gui_main(servosModel, reward);

    DynaQ * dyna = new DynaQ(servosModel, reward);

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

    char t;
    cin >> t;

    delete dyna;

    return 0;
}
