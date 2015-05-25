#include "Sonar.h"

using namespace std;

Sonar::Sonar(int pin_trigger, int pin_echo)
{
    trigger = pin_trigger;
    echo = pin_echo;
    isRaspberryPi = false;

    struct utsname sysinfo;
    uname(&sysinfo);
    //cout << "Your computer is : " << sysinfo.nodename << endl;
    std::string g = "raspberrypi";
    if ( g.compare(sysinfo.nodename) == 0) isRaspberryPi = true;  // if raspberry

    if (isRaspberryPi){
        wiringPiSetup ();
        pinMode(trigger, OUTPUT);
        pinMode(echo, INPUT);
    }

    _last_distance = 0;
}

int Sonar::waitforpin(int pin_value, int timeout_uS)
{
    struct timeval now, start;
    int done;
    int micros;
    gettimeofday(&start, NULL);
    micros = 0;
    done=0;
    while (!done)
    {
        gettimeofday(&now, NULL);
        if (now.tv_sec > start.tv_sec) micros = 1000000L;
        else micros = 0;
        micros = micros + (now.tv_usec - start.tv_usec);
        if (micros > timeout_uS) done=1;
        if (digitalRead(echo) == pin_value) done = 1;
    }
    return micros;
}

int Sonar::GetFilteredDistance(){
    if (!isRaspberryPi) return rand() % 100;

    int firstMeasure = GetDistance();
    delay(35);
    int secoundMeasure = GetDistance();

    if (-2 < (firstMeasure - secoundMeasure) && (firstMeasure - secoundMeasure) < 2) return firstMeasure;
    else {
        delay(35);
        int thirdMeasure = GetDistance();
        if (firstMeasure == thirdMeasure) return firstMeasure;
        if (secoundMeasure == thirdMeasure) return secoundMeasure;
    }
    delay(35);
    return GetFilteredDistance();
}

int Sonar::GetDistance()
{
    if (!isRaspberryPi) return -1;

    int l=400;

    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    waitforpin(HIGH, 5000);

    if (digitalRead(echo) ==HIGH)
    {
        l = waitforpin(LOW, 30000);

        if (digitalRead(echo) == LOW) l = l/ 58 + 1;
    }
    _last_distance = l;
    cout << "sonar: " << _last_distance << endl;
    return l;
}

int Sonar::getLastDistance ()
{
    return _last_distance;
}

