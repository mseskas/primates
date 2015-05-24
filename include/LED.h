#ifndef LED_H
#define LED_H
#include <wiringPi.h>
#include <sys/utsname.h>
#include <string>

class LED
{
    public:
        LED(int pinNo);

        void TurnON();
        void TurnOff();

        // 0 - off, 1 - on
        int State;
    protected:
    private:
        int pinNumber;
        bool isRaspberryPi;
};

#endif // LED_H
