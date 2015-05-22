#ifndef PWM_GTK_CONTROL_H
#define PWM_GTK_CONTROL_H

#include <gtk/gtk.h>
#include <gtk/gtkbutton.h>
#include "pwm_chip.h"
#include "servo.h"




class pwm_gtk_control
{
    public:
        pwm_gtk_control(char * title, int minVal, int maxVal, int startVal);
        GtkWidget * get_main();
        static void scale_value_changed(GtkWidget *wid, gpointer user_data);
        static void entry_changed(GtkWidget *wid, gpointer user_data);
        static void btnReleaseClick(GtkWidget *wid, gpointer user_data);
        static void btnOnClick(GtkWidget *wid, gpointer user_data);

        int minValue;
        int maxValue;
        int startValue;

        void SetServo(servo * servoMotor);

        bool isON;

    private:
        GtkWidget * frame;
        GtkWidget * fixed;
        GtkWidget * scale;  // GtkHScale
        GtkWidget * btnON;  //GtkButton
        GtkWidget * btnRelease; // GtkButton
        GtkWidget * minTxt;
        GtkWidget * maxTxt;

        int is_entry_changed;


        //int _servoPinNo;



        servo * ser;
};

#endif // PWM_GTK_CONTROL_H
