#ifndef PWM_GTK_CONTROL_H
#define PWM_GTK_CONTROL_H

#include <gtk/gtk.h>
#include <gtk/gtkbutton.h>
#include "pwm_chip.h"
#include "servo.h"
#include <string>  // std::string, std::stoi
#include <stdio.h> //
#include <stdlib.h> // itos

#include <sys/utsname.h>

class pwm_gtk_control
{
    public:
        pwm_gtk_control(char * title, int pinNo, int minVal, int maxVal);
        GtkWidget * get_main();
        static void scale_value_changed(GtkWidget *wid, gpointer user_data);
        static void entry_changed(GtkWidget *wid, gpointer user_data);
        static void btnReleaseClick(GtkWidget *wid, gpointer user_data);
        static void btnOnClick(GtkWidget *wid, gpointer user_data);

        int minValue;
        int maxValue;

    private:
        GtkWidget * frame;
        GtkWidget * fixed;
        GtkWidget * scale;  // GtkHScale
        GtkWidget * btnON;  //GtkButton
        GtkWidget * btnRelease; // GtkButton
        GtkWidget * minTxt;
        GtkWidget * maxTxt;

        int is_entry_changed;
        bool isON = false;

        int _servoPinNo;



        servo * ser;
        pwm_chip * chip;
};

#endif // PWM_GTK_CONTROL_H
