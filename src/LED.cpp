#include "LED.h"

LED::LED(int pinNo)
{
    pinNumber = pinNo;
    State = LOW;
    isRaspberryPi = false;

    struct utsname sysinfo;
    uname(&sysinfo);
    //cout << "Your computer is : " << sysinfo.nodename << endl;
    std::string g = "raspberrypi";
    if ( g.compare(sysinfo.nodename) == 0) isRaspberryPi = true;  // if raspberry

    if (isRaspberryPi){
        wiringPiSetup ();
        pinMode (pinNumber, OUTPUT);
        digitalWrite (pinNumber, LOW);
    }
}

void LED::TurnON(){
    if (isRaspberryPi) digitalWrite (pinNumber, HIGH);
    State = HIGH;
}

void LED::TurnOff(){
    if (isRaspberryPi) digitalWrite (pinNumber, LOW);
    State = LOW;
}
