#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <thread>
#include <sys/utsname.h>
#include "servo.h"
#include "gtkAllServo.h"
#include "pwm_gtk_control.h"


class gui_main
{
    public:
        gui_main( );

        void build_gui();

        void LoadServoControls(GtkWidget * frame);

        static const int srvQuantity = 12;

    protected:
    private:

        int _servoParams[srvQuantity][3] = {
            {25, 15, 40},
            {90, 60, 90},
            {50, 32, 60},
            {45, 25, 52},
            {37, 37, 70},
            {20, 10, 40},
            {45, 40, 65},
            {84, 47, 84},
            {50, 30, 75},
            {35, 20, 42},
            {10, 10, 40},
            {32, 15, 50}
        };

        servo * _servos[srvQuantity];

        GtkWidget * _window;
        GtkWidget * _fixed_box;
        std::thread * _execution_thread;
};

#endif // GUI_MAIN_H
