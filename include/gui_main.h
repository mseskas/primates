#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <thread>
#include <sys/utsname.h>
#include "Servo.h"
#include "gtkAllServo.h"
#include "pwm_gtk_control.h"
#include "RewardView.h"
#include "WalkView.h"

class gui_main
{
    public:
        gui_main(ServoModel * allServoModel, Reward * rewardModel);
        void build_gui();
        void LoadServoControls(GtkWidget * frame);

        int srvQuantity;

        static void btnAllOffClick(GtkWidget *wid, gpointer user_data);
        static void btnAllOnClick(GtkWidget *wid, gpointer user_data);

        pwm_gtk_control * PwmViews[12];

        ServoModel * ServosModel;
        Reward * RewardModel;

    protected:
    private:
        bool isRaspberryPi;


        GtkWidget * AllOffButton;
        GtkWidget * AllOnButton;
        GtkWidget * _window;
        GtkWidget * _pwmControlPage;
        GtkWidget * _positionPage;
        std::thread * _execution_thread;
};

#endif // GUI_MAIN_H
