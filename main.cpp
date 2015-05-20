#include <iostream>
#include <string>
#include "gui_main.h"
#include "MPU6050.h"
#include "Reward.h"

using namespace std;

int main()
{

    gui_main * main_gui = new gui_main();

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

    int t;
    cin >> t;
    return 0;
}
