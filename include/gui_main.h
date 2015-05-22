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

#include "RewardView.h"

class gui_main
{
    public:
        gui_main( );
        void build_gui();
        void LoadServoControls(GtkWidget * frame);
        static const int srvQuantity = 12;

        static void btnAllOffClick(GtkWidget *wid, gpointer user_data);
        static void btnAllOnClick(GtkWidget *wid, gpointer user_data);

        pwm_gtk_control * PwmViews[srvQuantity];
        servo * Servos[srvQuantity];
    protected:
    private:
        bool isRaspberryPi;
        int * _servoParams;

        GtkWidget * AllOffButton;
        GtkWidget * AllOnButton;
        GtkWidget * _window;
        GtkWidget * _pwmControlPage;
        GtkWidget * _positionPage;
        std::thread * _execution_thread;
};

#endif // GUI_MAIN_H
