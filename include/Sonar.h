
#ifndef SONAR_H
#define SONAR_H

#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include <thread>
#include <sys/time.h>
#include <project_constants.h>
#include <sys/utsname.h>
#include <string>


class Sonar
{
public:
    Sonar(int pin_trigger, int pin_echo);
    int getLastDistance();
    int get_trigger();
    void set_trigger(int pin_trigger);
    int get_echo();
    void set_echo(int pin_echo);

    int GetDistance();
    int GetFilteredDistance();

    bool isRaspberryPi;
private:

    int trigger;
    int echo;
    int waitforpin(int pin_value, int timeout_uS);
    int _last_distance;
};

#endif // SONAR_H
