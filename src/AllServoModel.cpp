#include "AllServoModel.h"

AllServoModel::AllServoModel()
{
    //
    int * params = new int[srvQuantity*3] {
            25, 15, 40,//
            90, 79, 90,
            55, 56, 70,
            45, 25, 52,//
            37, 37, 47,
            23, 5, 18,
            45, 40, 65,//
            84, 75, 84,
            58, 60, 74,
            35, 20, 42,//
            10, 10, 20,
            23, 10, 23
            };

    ServoParams = params;
    LastState = 0;
    LoadServoControls();
}

void AllServoModel::ReleaseMotors(){
    for (int i = 0; i < srvQuantity; i++) Servos[i]->Reset();
}

void AllServoModel::LoadServoControls(){
    pwm_chip * chip = NULL;
    chip = new pwm_chip(PWM_CHIP_ADDR);
   // servo ** temp = new servo*[srvQuantity];
   // Servos = &temp[0][0];
    for (int i = 0; i < srvQuantity; i++) Servos[i] = new servo(chip, i+1);
}

short AllServoModel::BeginState(){
    //string tmp = "010101010101";
    //strcpy(LastState, tmp.c_str());
    //short beginState = 1365;
    short beginState = 102;

    LastState = beginState;
    ExecutePosition(beginState);

    return LastState;
}

void AllServoModel::ExecutePosition(short state){
    int min = 0;
    int max = 0;
    double d = 0.0;

    int flags[srvQuantity];
    printf("changing state to: %hu\r\n", state);

    for (int f = 0; f < 8; f++){
        flags[srvQuantity-5 - f] = state % 2;
        state = state / 2;
    }
    int i =0;
    int flag = flags[0];
// first
    if (flag == 0){
        min = ServoParams[  1];
        d = (float)min / 100;
        Servos[i]->set_angle(d);
    } else {
        max = ServoParams[  2];
        d = (float)max / 100;
        Servos[0]->set_angle(d);
    }

    flag = flags[1];
    if (flag == 0){
        min = ServoParams[1*3 + 1];
            d = (float)min / 100;
           Servos[1]->set_angle(d);
    } else {
        max = ServoParams[1*3 + 2];
            d = (float)max / 100;
            Servos[1]->set_angle(d);
    }
// two
    flag = flags[2];
    if (flag == 0){
        min = ServoParams[3*3 + 1];
            d = (float)min / 100;
           Servos[3]->set_angle(d);
    } else {
        max = ServoParams[3*3 + 2];
            d = (float)max / 100;
            Servos[3]->set_angle(d);
    }

    flag = flags[3];
    if (flag == 0){
        min = ServoParams[4*3 + 1];
            d = (float)min / 100;
           Servos[4]->set_angle(d);
    } else {
        max = ServoParams[4*3 + 2];
            d = (float)max / 100;
            Servos[4]->set_angle(d);
    }
// three
    flag = flags[4];
    if (flag == 0){
        min = ServoParams[6*3 + 1];
            d = (float)min / 100;
           Servos[6]->set_angle(d);
    } else {
        max = ServoParams[6*3 + 2];
            d = (float)max / 100;
            Servos[6]->set_angle(d);
    }

    flag = flags[5];
    if (flag == 0){
        min = ServoParams[7*3 + 1];
            d = (float)min / 100;
           Servos[7]->set_angle(d);
    } else {
        max = ServoParams[7*3 + 2];
            d = (float)max / 100;
            Servos[7]->set_angle(d);
    }
// four
    flag = flags[6];
    if (flag == 0){
        min = ServoParams[9*3 + 1];
            d = (float)min / 100;
           Servos[9]->set_angle(d);
    } else {
        max = ServoParams[9*3 + 2];
            d = (float)max / 100;
            Servos[9]->set_angle(d);
    }

    flag = flags[7];
    if (flag == 0){
        min = ServoParams[10*3 + 1];
            d = (float)min / 100;
           Servos[10]->set_angle(d);
    } else {
        max = ServoParams[10*3 + 2];
            d = (float)max / 100;
            Servos[10]->set_angle(d);
    }



//    for (int i = 0; i < srvQuantity; i++){
//
//
//        if (flag == 0){
//            min = ServoParams[i*3 + 1];
//                d = (float)min / 100;
//               Servos[i]->set_angle(d);
//        } else {
//            max = ServoParams[i*3 + 2];
//                d = (float)max / 100;
//                Servos[i]->set_angle(d);
//        }
//    }
}


// Possible data12[x] values : "0", "1" or any other
void AllServoModel::ExecutePosition(const char * data12){
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
}



