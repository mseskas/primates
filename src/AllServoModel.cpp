#include "AllServoModel.h"

AllServoModel::AllServoModel()
{
    //
    int * params = new int[srvQuantity*3] {
            25, 15, 40,//
            90, 80, 90,
            55, 55, 70,
            45, 25, 52,//
            37, 37, 50,
            23, 10, 23,
            45, 40, 65,//
            84, 70, 84,
            58, 58, 68,
            35, 20, 42,//
            10, 10, 20,
            23, 15, 23
            };


    ServoParams = params;

    LoadServoControls();
}


void AllServoModel::LoadServoControls(){
    pwm_chip * chip = NULL;
    chip = new pwm_chip(PWM_CHIP_ADDR);

   // servo ** temp = new servo*[srvQuantity];

   // Servos = &temp[0][0];

    for (int i = 0; i < srvQuantity; i++) Servos[i] = new servo(chip, i+1);
}

//LastPosition = "x10x01x10x01";
char* AllServoModel::BeginState(){
    string tmp = "x10x01x10x01";
    strcpy(LastState, tmp.c_str());

    ExecutePosition(LastState);

    return LastState;
}

int AllServoModel::ExecutePosition(short state){
    int min = 0;
    int max = 0;
    double d = 0.0;

    int flags[srvQuantity];

    for (int f = 0; f < srvQuantity; f++){
        flags[f] = state % 2;
    }

    printf("changing state to: ");
    printf(data12);
    printf("\r\n");

    for (int i = 0; i < srvQuantity; i++){
        char cr = data12[i];

        switch (cr){
            case '0':
                min = ServoParams[i*3 + 1];
                d = (float)min / 100;
               Servos[i]->set_angle(d);

            break;
            case '1':
                max = ServoParams[i*3 + 2];
                d = (float)max / 100;
                Servos[i]->set_angle(d);
            break;
            default:
            break;
        }
    }
    return 1;
}


// Possible data12[x] values : "0", "1" or any other
int AllServoModel::ExecutePosition(char * data12){
    int min = 0;
    int max = 0;
    double d = 0.0;

    printf("changing state to: ");
    printf(data12);
    printf("\r\n");

    for (int i = 0; i < srvQuantity; i++){
        char cr = data12[i];

        switch (cr){
            case '0':
                min = ServoParams[i*3 + 1];
                d = (float)min / 100;
               Servos[i]->set_angle(d);

            break;
            case '1':
                max = ServoParams[i*3 + 2];
                d = (float)max / 100;
                Servos[i]->set_angle(d);
            break;
            default:
            break;
        }
    }
    return 1;
}



