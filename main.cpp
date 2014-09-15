#include <iostream>
#include <string>





#include "gui_main.h"


#include "MPU6050.h"

using namespace std;

int main()
{

   // gui_main * main_gui = new gui_main();
   try {
        MPU6050 * chip = new MPU6050();
        cout << "starting..." << endl;
        for (int i = 0; i < 100000; i++)
        {
            cout << chip->GetAccelX() << "\t" << chip->GetAccelY() << "\t" << chip->GetAccelZ()<< endl;
            delay(100);
        }

        int cmd;

        cin >> cmd;
   }
    catch (...)
    {

        cout << "fff";
        cin;
    }

    return 0;
}
